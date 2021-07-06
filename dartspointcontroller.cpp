#include "dartspointcontroller.h"

using namespace DartsPointControllerContext;

void DartsPointController ::start()
{
    sendCurrentTurnValues();
}

void DartsPointController::stop()
{
    emit controllerIsStopped();
}

void DartsPointController::handleAndProcessUserInput(const QByteArray& json)
{
    auto dartsPointModel = _pointModelBuilder->createPointModel(json);
    _calculateScoreByPointInput->addScoreValueToDartsPointModel(dartsPointModel);
    auto setIndex = _indexService->setIndex();
    auto accumulatedScore = _inputService->calculateAccumulatedScoreCandidate(setIndex,dartsPointModel->score());
    auto domain = _inputEvaluator->validateInput(accumulatedScore,
                                                  dartsPointModel->modKeyCode(),
                                                  dartsPointModel->point());
    processDomain(domain,dartsPointModel->point(),dartsPointModel->score(),dartsPointModel->modKeyCode());
}

void DartsPointController::handleRequestForCurrentTournamentMetaData()
{
    emit sendCurrentTournamentId(_metaData->tournamentId());
}

void DartsPointController::handleRequestOrderedDartsPoints()
{
    emit requestDartsPointsOrderedByIndexes(_metaData->tournamentId());
}

void DartsPointController::handlePointAddedToDataContext(const QByteArray &json)
{
    if(_metaData->status() == WinnerDeclared)
        sendWinnerJson();
    else
        createAndSendTurnValues(json);
}

void DartsPointController::handleResetTournament()
{
    _indexService->reset();
    _inputService->resetScores();
    emit requestResetTournament(_metaData->tournamentId());
}

void DartsPointController::sendCurrentTurnValues()
{
    auto turnValues = _turnValuesBuilder->createTurnValues(_indexService,_inputService,
                                                           _stringSuggestionService);
    emit awaitsInput(turnValues->toJson());
}

QString DartsPointController::currentPlayerName()
{
    auto index = _indexService->setIndex();
    auto playerName = _inputService->playerName(index);
    return playerName;
}

QUuid DartsPointController::currentPlayerId()
{
    auto index = _indexService->setIndex();
    auto playerID = _inputService->playerIdAtIndex(index);
    return playerID;
}

int DartsPointController::lastPlayerIndex()
{
    auto playerCount = _inputService->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid DartsPointController::undoTurn()
{
    if(_metaData->status() == ControllerState::WinnerDeclared)
        return QUuid();
    _indexService->undo();
    auto roundIndex = _indexService->roundIndex();
    auto attemptIndex = _indexService->attemptIndex();
    emit hideDartsPoint(_metaData->tournamentId(),currentPlayerId(),roundIndex,attemptIndex);
    return currentPlayerId();
}

QUuid DartsPointController::redoTurn()
{
    auto activeUser = currentPlayerId();
    auto roundIndex = _indexService->roundIndex();
    auto attemptIndex = _indexService->attemptIndex();
    emit revealDartsPoint(_metaData->tournamentId(),activeUser,roundIndex,attemptIndex);
    auto index = _indexService->setIndex();
    return _inputService->playerIdAtIndex(index);
}

void DartsPointController::addPoint(const int& point,
                                    const int &score,
                                    const int& keyCode)
{
    auto pointModel = _pointModelBuilder->createPointModel(point,score,keyCode);
    auto playerModel = _playerModelBuilder->createPlayerModelByValues(currentPlayerId(),currentPlayerName());
    updatePlayerPointModel(pointModel, currentPlayerId());
    auto indexes = _dartsIndexesBuilder->buildControllerIndexesByIndexService(_indexService);
    auto json = createJsonResponse(indexes,playerModel,pointModel);
    emit requestAddDartsPoint(json);
}

void DartsPointController::handleRequestFromUI()
{
    if(_metaData->status() == ControllerState::WinnerDeclared)
        sendWinnerJson();
    else
        emit controllerInitializedAndReady();
}

void DartsPointController::nextTurn()
{
    _indexService->syncIndex();
    _indexService->next();
}

void DartsPointController::declareWinner()
{
    auto index = _indexService->setIndex();
    auto currentPlayerId = _inputService->playerIdAtIndex(index);
    _inputService->setWinner(currentPlayerId);
    _metaData->setStatus(WinnerDeclared);
}

void DartsPointController::handleOrderedDartsPoint(const QByteArray &json)
{
    QByteArray jsonResponse = json;
    _addTotalScoresToDartsModelsJson->addTotalScoreToInputs(jsonResponse,_inputService->initialScore());
    _addPlayerNamesToDartsModelsJson->addPlayerNamesToJson(jsonResponse,_inputService);
    emit sendOrderedDartsPoints(jsonResponse);
}

void DartsPointController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = _dartsIndexesBuilder->buildControllerIndexesByJson(json);
    _indexService->setIndexes(indexes);
    emit requestTournamentAssignedPlayerDetails(_metaData->tournamentId());
}

void DartsPointController::processDomain(const int& domain,
                                         const int& point,
                                         const int &score,
                                         const int& modKeyCode)
{
    switch (domain)
    {
        // In case user enters scores above 180
        case OutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addPoint(point,score,modKeyCode);break;
        case CriticalDomain : addPoint(point,score,modKeyCode);break;
        case TargetDomain : {
            declareWinner();
            addPoint(point,score,modKeyCode);
            break;
        }
        case OutsideDomain : addPoint(0,0,modKeyCode);break;
    }
}

void DartsPointController::beginInitialize()
{
    auto tournamentId = _metaData->tournamentId();
    emit requestDartsTournamentIndexes(tournamentId);
}

void DartsPointController::undoSuccess(const QByteArray& json)
{
    QScopedPointer<const IControllerPoint> dartsPointModel(_pointModelBuilder->createPointModel(json));
    _calculateScoreByPointInput->addScoreValueToDartsPointModel(dartsPointModel.get());
    _inputService->addPlayerScore(dartsPointModel.get());
    auto newScore = _inputService->playerScore(dartsPointModel->playerId());
    QScopedPointer<const IControllerPoint> alteredDartsPointModel( _pointModelBuilder->createPointModelWithTotalScoreByModel(dartsPointModel.get(),newScore));
    auto playerName = _inputService->playerName(dartsPointModel->playerId());
    QScopedPointer<const ControllerPlayer> playerModel(_playerModelBuilder->createPlayerModelByValues(dartsPointModel->playerId(),playerName));
    QScopedPointer<const DartsPointTurnValues> turnValues(_turnValuesBuilder->createTurnValues(_indexService,_inputService,
                                                          _stringSuggestionService));
    auto response = createJsonResponse(alteredDartsPointModel.get(),playerModel.get(),turnValues.get());
    emit pointRemoved(response);
}

void DartsPointController::redoSuccess(const QByteArray& json)
{
    auto pointModel = _pointModelBuilder->createPointModel(json);
    _calculateScoreByPointInput->addScoreValueToDartsPointModel(pointModel);
    _inputService->subtractPlayerScore(pointModel);
    auto newScore = _inputService->playerScore(pointModel->playerId());
    pointModel = _pointModelBuilder->createPointModelWithTotalScoreByModel(pointModel,newScore);
    auto playerName = _inputService->playerName(pointModel->playerId());
    auto playerModel = _playerModelBuilder->createPlayerModelByValues(pointModel->playerId(),playerName);
    _indexService->redo();
    auto turnControllerValues = _turnValuesBuilder->createTurnValues(_indexService,_inputService,
                                                                                _stringSuggestionService);
    auto jsonResponse = createJsonResponse(pointModel,playerModel,turnControllerValues);
    emit dartsPointPersisted(jsonResponse);
}

void DartsPointController::createAndSendTurnValues(const QByteArray &json)
{
    QScopedPointer<const IControllerPoint> pointModel(_pointModelBuilder->createPointModel(json));
    subtractAndAddScoreValuesToModel(pointModel.get());
    QScopedPointer<const ControllerPlayer> playerModel(_playerModelBuilder->createPlayerModelByValues(pointModel->playerId(),currentPlayerName()));
    nextTurn();
    QScopedPointer<const DartsPointTurnValues> turnValues(_turnValuesBuilder->createTurnValues(_indexService,_inputService,_stringSuggestionService));
    auto jsonResponse = createJsonResponse(pointModel.get(),playerModel.get(),turnValues.get());
    emit dartsPointPersisted(jsonResponse);
}

void DartsPointController::subtractAndAddScoreValuesToModel(const IControllerPoint *pointModel)
{
    _calculateScoreByPointInput->addScoreValueToDartsPointModel(pointModel);
    auto totalScoreValue = _inputService->subtractPlayerScore(pointModel);
    _addTotalScoreToPointModel->add(pointModel,totalScoreValue);
}

void DartsPointController::sendWinnerJson()
{
    auto winnerName = _inputService->winnerName();
    auto winnerId = _inputService->winnerId();
    auto jsonResponse = createJsonResponse(winnerId,winnerName);
    emit winnerDeclared(jsonResponse);
}

void DartsPointController::updatePlayerPointModel(const IControllerPoint *pointModel, const int &score)
{
    _controllerModels->addAccumulatedScoreToModel(pointModel,score);
}

QByteArray DartsPointController::createJsonResponse(const IControllerPoint *pointModel,
                                                      const ControllerPlayer* playerModel,
                                                      const DartsPointTurnValues *turnValues)
{
    auto jsonResponse = _jsonMerger->createJsonFromList({pointModel->toJson(),playerModel->toJson(),
                                                         turnValues->toJson()});
    return jsonResponse;
}

void DartsPointController::updatePlayerPointModel(const IControllerPoint *pointModel, const QUuid &playerId)
{
    _controllerModels->addPlayerIdToModel(pointModel,playerId);
}

QByteArray DartsPointController::createJsonResponse(const QUuid &winnerId, const QString &winnerName)
{
    auto jsonResponse = _jsonMerger->createJsonFromList({_jsonBuilder->createJson(winnerName,"winnerName"),
                                                         _jsonBuilder->createJson(winnerId,"winnerId"),
                                                         _jsonBuilder->createJson(_metaData->tournamentId(),"tournamentId")});
    return jsonResponse;
}

QByteArray DartsPointController::createJsonResponse(const DartsIndexes *indexes,
                                                      const ControllerPlayer *playerModel,
                                                      const IControllerPoint *pointModel)
{
    auto json = _jsonMerger->createJsonFromList({_jsonBuilder->createJson(_metaData->tournamentId(),"tournamentId"),
                                                 indexes->toJson(),playerModel->toJson(),pointModel->toJson()});
    return json;
}

void DartsPointController::initializeControllerPlayerDetails(const QByteArray& json)
{
    auto playerModels = _playerModelBuilder->createPlayerModelsByJson(json);
    _indexService->setPlayersCount(playerModels.count());
    _inputService->addPlayerEntitiesByModels(playerModels);
    emit requestTournamentDartsPoints(_metaData->tournamentId());
}

void DartsPointController::initializeControllerDartsPoints(const QByteArray& json)
{
    auto points = _pointModelBuilder->createPointsByJson(json);
    _calculateScoreByPointInput->addScoreValuesToDartsPointModels(points);
    _inputService->subtractPlayerScoresByModels(points);
    emit requestTournamentWinnerIdAndName(_metaData->tournamentId());
}

void DartsPointController::initializeControllerWinnerIdAndName(const QByteArray& json)
{
    auto winnerId = _jsonExtractor->getIdValueByKey(json,"winnerId");
    _inputService->setWinner(winnerId);
    emit controllerInitialized(_metaData->displayHint());
}
