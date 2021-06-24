#include "dartspointcontroller.h"

using namespace DartsPointControllerContext;

void DartsPointController ::start()
{
    sendCurrentTurnValues();
}

void DartsPointController::stop()
{
    // No implementation necessary since this is handled by external frontend
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
    auto tournament = _tournament;
    emit sendCurrentTournamentId(tournament);
}

void DartsPointController::handleRequestOrderedDartsPoints()
{
    auto tournamentId = _tournament;
    emit requestDartsPointsOrderedByIndexes(tournamentId);
}

void DartsPointController::handlePointAddedToDataContext(const QByteArray &json)
{
    auto pointModel = _pointModelBuilder->createPointModel(json);
    subtractAndAddScoreValuesToModel(pointModel);
    auto playerModel = _playerModelBuilder->createPlayerModelByValues(pointModel->playerId(),currentPlayerName());
    nextTurn();
    auto turnValues = _turnValuesBuilder->createTurnValues(_indexService,_inputService,_stringSuggestionService);
    auto jsonResponse = createResponseAsJson(pointModel,playerModel,turnValues);
    emit dartsPointPersisted(jsonResponse);
}

void DartsPointController::handleResetTournament()
{
    _indexService->reset();
    _inputService->resetScores();
    auto tournamentId = _tournament;
    emit requestResetTournament(tournamentId);
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
    if(_status == ControllerState::WinnerDeclared)
        return QUuid();
    _indexService->undo();
    auto roundIndex = _indexService->roundIndex();
    auto attemptIndex = _indexService->attemptIndex();
    emit hideDartsPoint(_tournament,currentPlayerId(),roundIndex,attemptIndex);
    return currentPlayerId();
}

QUuid DartsPointController::redoTurn()
{
    auto activeUser = currentPlayerId();
    auto roundIndex = _indexService->roundIndex();
    auto attemptIndex = _indexService->attemptIndex();
    emit revealDartsPoint(_tournament,activeUser,roundIndex,attemptIndex);
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
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByIndexService(_indexService);
    auto json = createResponseAsJson(indexes,playerModel,pointModel);
    emit requestAddDartsPoint(json);
}

void DartsPointController::handleRequestFromUI()
{
    if(_status == ControllerState::WinnerDeclared)
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
    setCurrentStatus(ControllerState::WinnerDeclared);
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
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByJson(json);
    _indexService->setIndexes(indexes);
    emit requestTournamentAssignedPlayerDetails(_tournament);
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

void DartsPointController::setCurrentStatus(int currentStatus)
{
    _status = currentStatus;
}

void DartsPointController::beginInitialize()
{
    auto tournamentId = _tournament;
    emit requestDartsTournamentIndexes(tournamentId);
}

void DartsPointController::undoSuccess(const QByteArray& json)
{
    auto dartsPointModel = _pointModelBuilder->createPointModel(json);
    _calculateScoreByPointInput->addScoreValueToDartsPointModel(dartsPointModel);
    _inputService->addPlayerScore(dartsPointModel);
    auto newScore = _inputService->playerScore(dartsPointModel->playerId());
    dartsPointModel = _pointModelBuilder->createPointModelWithTotalScoreByModel(dartsPointModel,newScore);
    auto playerName = _inputService->playerName(dartsPointModel->playerId());
    auto playerModel = _playerModelBuilder->createPlayerModelByValues(dartsPointModel->playerId(),playerName);
    auto turnValues = _turnValuesBuilder->createTurnValues(_indexService,_inputService,
                                                                      _stringSuggestionService);
    auto response = createResponseAsJson(dartsPointModel,playerModel,turnValues);
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
    auto jsonResponse = createResponseAsJson(pointModel,playerModel,turnControllerValues);
    emit dartsPointPersisted(jsonResponse);
}

DartsPointController::DartsPointController(const QUuid &tournament, const int &displayHint)
{
    _tournament = tournament;
    _displayHint = displayHint;
}

void DartsPointController::subtractAndAddScoreValuesToModel(const IControllerPoint *pointModel)
{
    _calculateScoreByPointInput->addScoreValueToDartsPointModel(pointModel);
    auto totalScoreValue = _inputService->subtractPlayerScore(pointModel);
    _addTotalScoreToPointModel->add(pointModel,totalScoreValue);
}

void DartsPointController::sendWinnerJson()
{
    auto winnerName = _inputService->winnerUserName();
    auto json = _dartsJsonService->createJsonByWinnerName(winnerName);
    emit winnerDeclared(json);
}

void DartsPointController::updatePlayerPointModel(const IControllerPoint *pointModel, const int &score)
{
    _controllerModelsService->addAccumulatedScoreToModel(pointModel,score);
}

QByteArray DartsPointController::createResponseAsJson(const IControllerPoint *pointModel,
                                                      const ControllerPlayer* playerModel,
                                                      const DartsPointTurnValues *turnValues)
{
    QByteArray json;
    _combineJsonService->addToJson(json,pointModel->toJson());
    _combineJsonService->addToJson(json,playerModel->toJson());
    _combineJsonService->addToJson(json,turnValues->toJson());
    return json;
}

void DartsPointController::updatePlayerPointModel(const IControllerPoint *pointModel, const QUuid &playerId)
{
    _controllerModelsService->addPlayerIdToModel(pointModel,playerId);
}

QByteArray DartsPointController::createResponseAsJson(const DartsIndexes *indexes,
                                                      const ControllerPlayer *playerModel,
                                                      const IControllerPoint *pointModel)
{
    auto tournamentJson = _dartsJsonService->createJsonByTournamentId(_tournament);
    QByteArray json;
    _combineJsonService->addToJson(json,indexes->toJson());
    _combineJsonService->addToJson(json,playerModel->toJson());
    _combineJsonService->addToJson(json,pointModel->toJson());
    _combineJsonService->addToJson(json,tournamentJson);
    return json;
}

void DartsPointController::initializeControllerPlayerDetails(const QByteArray& json)
{
    auto playerModels = _playerModelBuilder->createPlayerModelsByJson(json);
    _indexService->setPlayersCount(playerModels.count());
    _inputService->addPlayerEntitiesByModels(playerModels);
    emit requestTournamentDartsPoints(_tournament);
}

void DartsPointController::initializeControllerDartsPoints(const QByteArray& json)
{
    auto points = _pointModelBuilder->createPointsByJson(json);
    _calculateScoreByPointInput->addScoreValuesToDartsPointModels(points);
    _inputService->subtractPlayerScoresByModels(points);
    emit requestTournamentWinnerIdAndName(_tournament);
}

void DartsPointController::initializeControllerWinnerIdAndName(const QByteArray& json)
{
    auto winnerId = _dartsJsonService->getWinnerIdByJson(json);
    _inputService->setWinner(winnerId);
    emit controllerInitialized(_displayHint);
}
