#include "dpcontroller.h"

using namespace DPCContext;

void DPController ::start()
{
    sendCurrentTurnValues();
}

void DPController::stop()
{
    emit controllerIsStopped();
}

void DPController::handleAndProcessUserInput(const QByteArray& json)
{
    auto dartsPointModel = _pointModelBuilder->createModel(json);
    _calculateScoreByPointInput->calculateScore(dartsPointModel);
    auto accumulatedScore = subTractScore()->getTotalScoreCandidate(dartsPointModel,scoresService());
    auto domain = _inputEvaluator->validateInput(accumulatedScore,
                                                  dartsPointModel->modKeyCode(),
                                                  dartsPointModel->point());
    processDomain(domain,dartsPointModel->point(),dartsPointModel->score(),dartsPointModel->modKeyCode());
}

void DPController::handleRequestForCurrentTournamentMetaData()
{
    emit sendCurrentTournamentId(_metaData->tournamentId());
}

void DPController::requestOrderedDartsPoints()
{
    emit requestDartsPointsOrderedByIndexes(_metaData->tournamentId());
}

void DPController::handlePointAddedToDataContext(const QByteArray &json)
{
    if(_metaData->status() == WinnerDeclared)
        sendWinnerJson();
    else
        createAndSendTurnValues(json);
}

void DPController::handleResetTournament()
{
    _indexService->reset();
    scoresService()->resetTuples(_metaData);
    emit requestResetTournament(_metaData->tournamentId());
}

void DPController::sendCurrentTurnValues()
{
    auto turnValues = _turnValuesBuilder->createTurnValues(_indexService,scoresService(),_stringSuggestionService);
    emit awaitsInput(turnValues->toJson());
}

QString DPController::currentPlayerName()
{
    auto index = _indexService->setIndex();
    auto playerName = scoresService()->tuples().at(index).name;
    return playerName;
}

QUuid DPController::currentPlayerId()
{
    auto index = _indexService->setIndex();
    return scoresService()->tuples().at(index).id;
}

int DPController::lastPlayerIndex()
{
    auto playerCount = scoresService()->tuples().count();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


void DPController::undoTurn()
{
    if(_metaData->status() == ControllerState::WinnerDeclared)
        return;
    _indexService->undo();
    auto roundIndex = _indexService->roundIndex();
    auto attemptIndex = _indexService->attemptIndex();
    emit hideDartsPoint(_metaData->tournamentId(),currentPlayerId(),roundIndex,attemptIndex);

}

void DPController::redoTurn()
{
    auto activeUser = currentPlayerId();
    auto roundIndex = _indexService->roundIndex();
    auto attemptIndex = _indexService->attemptIndex();
    emit revealDartsPoint(_metaData->tournamentId(),activeUser,roundIndex,attemptIndex);
}

void DPController::addPoint(const int& point,
                                    const int &score,
                                    const int& keyCode)
{
    auto pointModel = _pointModelBuilder->createModel(point,score,keyCode);
    auto playerModel = _playerModelBuilder->createPlayerModelByValues(currentPlayerId(),currentPlayerName());
    _controllerModels->addPlayerIdToModel(pointModel,playerModel->playerId());
    auto indexes = _dartsIndexesBuilder->createIndexes(_indexService);
    auto json = createJsonResponse(indexes,playerModel,pointModel);
    emit requestAddDartsPoint(json);
}

void DPController::handleRequestFromUI()
{
    if(_metaData->status() == ControllerState::WinnerDeclared)
        sendWinnerJson();
    else
        emit controllerInitializedAndReady();
}

void DPController::nextTurn()
{
    _indexService->syncIndex();
    _indexService->next();
}

void DPController::declareWinner()
{
    auto index = _indexService->setIndex();
    auto currentPlayerId = scoresService()->tuples().at(index).id;
    _inputService->setWinner(currentPlayerId);
    _metaData->setStatus(WinnerDeclared);
}

void DPController::handleOrderedDartsPoint(const QByteArray &json)
{
    QByteArray jsonResponse = json;
    addTotalScoresToDartsModelsJson()->addTotalScoreToInputs(jsonResponse,_metaData->initialScore());
    addPlayerNamesToDartsModelsJson()->addPlayerNamesToJson(jsonResponse,_inputService);
    emit sendOrderedDartsPoints(jsonResponse);
}

void DPController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = _dartsIndexesBuilder->createIndexes(json);
    _indexService->setIndexes(indexes);
    emit requestTournamentAssignedPlayerDetails(_metaData->tournamentId());
}

void DPController::processDomain(const int& domain, const int& point, const int &score, const int& modKeyCode)
{
    switch (domain)
    {
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

void DPController::beginInitialize()
{
    auto tournamentId = _metaData->tournamentId();
    emit requestDartsTournamentIndexes(tournamentId);
}

void DPController::undoSuccess(const QByteArray& json)
{
    QScopedPointer<IDPCModel> inputModel(_pointModelBuilder->createModel(json));
    auto score = _calculateScoreByPointInput->calculateScore(inputModel.get());
    inputModel->setScore(score);
    _inputService->updatePlayerScore(inputModel.get()); // TODO: Create service that updates total player score
    auto totalScore = getPlayerScore()->playerScore(inputModel->playerId(),scoresService());
    inputModel->setTotalScore(totalScore);
    auto playerName = _inputService->playerName(inputModel->playerId());
    QScopedPointer<const DCContext::IDCPlayer> playerModel(_playerModelBuilder->createPlayerModelByValues(inputModel->playerId(),playerName));
    QScopedPointer<const DartsPointTurnValues> turnValues(_turnValuesBuilder->createTurnValues(_indexService,scoresService(),
                                                          _stringSuggestionService));
    auto response = createJsonResponse(inputModel.get(),playerModel.get(),turnValues.get());
    emit pointRemoved(response);
}

void DPController::redoSuccess(const QByteArray& json)
{
    QScopedPointer<DPCContext::IDPCModel> pointModel(_pointModelBuilder->createModel(json));
    _calculateScoreByPointInput->calculateScore(pointModel.get());
    auto totalScore = _inputService->subtractPlayerScore(pointModel.get());
    pointModel->setTotalScore(totalScore);
    auto playerName = _inputService->playerName(pointModel->playerId());
    auto playerModel = _playerModelBuilder->createPlayerModelByValues(pointModel->playerId(),playerName);
    _indexService->redo();
    auto turnControllerValues = _turnValuesBuilder->createTurnValues(_indexService,scoresService(),_stringSuggestionService);
    auto jsonResponse = createJsonResponse(pointModel.get(),playerModel,turnControllerValues);
    emit dartsPointPersisted(jsonResponse);
}

void DPController::createAndSendTurnValues(const QByteArray &json)
{
    QScopedPointer<const IDPCModel> pointModel(_pointModelBuilder->createModel(json));
    subtractAndAddScoreValuesToModel(pointModel.get());
    QScopedPointer<const DCContext::IDCPlayer> playerModel(_playerModelBuilder->createPlayerModelByValues(pointModel->playerId(),currentPlayerName()));
    nextTurn();
    QScopedPointer<const DartsPointTurnValues>
            turnValues(_turnValuesBuilder->createTurnValues(_indexService,scoresService(),_stringSuggestionService));
    auto jsonResponse = createJsonResponse(pointModel.get(),playerModel.get(),turnValues.get());
    emit dartsPointPersisted(jsonResponse);
}

void DPController::subtractAndAddScoreValuesToModel(const IDPCModel *pointModel)
{
    _calculateScoreByPointInput->calculateScore(pointModel);
    auto totalScoreValue = _inputService->subtractPlayerScore(pointModel);
    _addTotalScoreToPointModel->add(pointModel,totalScoreValue);
}

void DPController::sendWinnerJson()
{
    auto winnerName = _inputService->winnerName();
    auto winnerId = _inputService->winnerId();
    auto jsonResponse = createJsonResponse(winnerId,winnerName);
    emit winnerDeclared(jsonResponse);
}


QByteArray DPController::createJsonResponse(const IDPCModel *pointModel,
                                            const DCContext::IDCPlayer *playerModel,
                                            const DartsPointTurnValues *turnValues)
{
    auto jsonResponse = jsonMerger()->createJsonFromList(
                {
                    createJsonFromPoint()->createJson(pointModel),
                    createJsonFromPlayer()->createJson(playerModel),
                    turnValues->toJson()
                });
    return jsonResponse;
}

QByteArray DPController::createJsonResponse(const QUuid &winnerId, const QString &winnerName)
{
    auto jsonResponse = jsonMerger()->createJsonFromList({jsonBuilder()->createJson(winnerName,"winnerName"),
                                                          jsonBuilder()->createJson(winnerId,"winnerId"),
                                                          jsonBuilder()->createJson(_metaData->tournamentId(),"tournamentId")});
    return jsonResponse;
}

QByteArray DPController::createJsonResponse(const IDPCIndexes *indexes, const DCContext::IDCPlayer *playerModel, const IDPCModel *pointModel)
{
    auto json = jsonMerger()->createJsonFromList(
                {
                    jsonBuilder()->createJson(_metaData->tournamentId(),"tournamentId"),
                    indexes->toJson(),
                    createJsonFromPlayer()->createJson(playerModel),
                    createJsonFromPoint()->createJson(pointModel)
                });
    return json;
}

void DPController::initializeControllerPlayerDetails(const QByteArray& json)
{
    auto playerModels = _playerModelBuilder->createPlayerModelsByJson(json);
    _indexService->setPlayersCount(playerModels.count());
    scoresService()->createTuples(playerModels,_metaData);
    emit requestTournamentDartsPoints(_metaData->tournamentId());
}

void DPController::initializeControllerDartsPoints(const QByteArray& json)
{
    auto points = _pointModelBuilder->createModels(json);
    _calculateScoreByPointInput->addScoreValuesToDartsPointModels(points);
    _inputService->subtractPlayerScore(points);
    emit requestTournamentWinnerIdAndName(_metaData->tournamentId());
}

void DPController::initializeControllerWinnerIdAndName(const QByteArray& json)
{
    auto winnerId = jsonExtractor()->getIdValueByKey(json,"winnerId");
    auto status = _determineControllerStateByWinnerId->service(winnerId);
    _metaData->setStatus(status);
    _inputService->setWinner(winnerId);
    emit controllerInitialized(_metaData->displayHint());
}
