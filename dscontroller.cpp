#include "dscontroller.h"

void DSController::start()
{
    sendCurrentTurnValues();
}

void DSController::stop()
{
    emit controllerIsStopped();
}

void DSController::handleAndProcessUserInput(const QByteArray& json)
{
    auto scoreCandidate = extractJson()->getIntegerValueByKey(json,"score");
    auto setIndex = _indexService->setIndex();
    auto accumulatedScore = calcAccScoreCand()->scoreCandidate(setIndex,scoreCandidate,scoresService());
    auto domain = _inputEvaluator->validateInput(accumulatedScore);
    processDomain(domain,scoreCandidate);
}

void DSController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = _metaData->tournamentId();
    emit sendCurrentTournamentId(tournament);
}

void DSController::createOrderedDartsScores()
{
    auto dartsScoreModels = _dartsScoreBuilder->createScoreModels(scoresService());
    auto json = createJsonFromDSModels()->createJson(dartsScoreModels);
    emit sendMultiAttemptDartsScores(json);
}

void DSController::handleRequestDartsScores()
{
    auto tournamentId = _metaData->tournamentId();
    emit requestDartsScores(tournamentId);
}

void DSController::handleScoreAddedToDataContext(const QByteArray &json)
{
    if(_metaData->status() == WinnerDeclared)
        createAndSendWinnerValues();
    else
        createAndSendTurnValues(json);
}

void DSController::handleResetTournament()
{
    _indexService->reset();
    scoresService()->resetTuples(_metaData);
    auto tournamentId = _metaData->tournamentId();
    emit requestResetTournament(tournamentId);
}

void DSController::sendCurrentTurnValues()
{
    auto model = _turnValuesBuilder->createTurnValues(_indexService,scoresService(),_scoreLogisticInterface);
    emit awaitsInput(model->toJson());
}

QString DSController::currentPlayerName()
{
    auto index = _indexService->setIndex();
    auto playerName = scoresService()->tuples().at(index).name;
    return playerName;
}

QUuid DSController::currentPlayerId()
{
    auto index = _indexService->setIndex();
    auto playerID = scoresService()->tuples().at(index).id;
    return playerID;
}

int DSController::lastPlayerIndex()
{
    auto playerCount = scoresService()->tuples().count();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


void DSController::undoTurn()
{
    if(_metaData->status() == ControllerState::WinnerDeclared)
        return;
    _indexService->undo();
    auto roundIndex = _indexService->roundIndex();
    emit hideDartsScore(_metaData->tournamentId(),currentPlayerId(),roundIndex);
}

void DSController::redoTurn()
{
    auto activeUser = currentPlayerId();
    auto roundIndex = _indexService->roundIndex();
    emit revealDartsScore(_metaData->tournamentId(), activeUser, roundIndex);
}

void DSController::addScore(const int& score)
{
    auto indexes = _dartsIndexesBuilderService->createIndexes(_indexService);
    auto scoreModel = _dartsScoreBuilder->createScoreModel(score);
    auto playerModel = _playerBuilderService->createModel(currentPlayerId(),currentPlayerName());
    auto json = createJsonResponse(scoreModel,indexes,playerModel);
    emit requestAddDartsScore(json);
}

void DSController::handleRequestFromUI()
{
    if(_metaData->status() == ControllerState::WinnerDeclared)
        createAndSendWinnerValues();
    else
        emit controllerInitializedAndReady();
}

void DSController::nextTurn()
{
    _indexService->next();
    sendCurrentTurnValues();
}

void DSController::declareWinner()
{
    _winnerService->setWinner(currentPlayerId(), currentPlayerName());
    _metaData->setStatus(ControllerState::WinnerDeclared);
}

void DSController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = _dartsIndexesBuilderService->createIndexes(json);
    _indexService->setIndexes(indexes);
    emit requestTournamentAssignedPlayerDetails(_metaData->tournamentId());
}

void DSController::processDomain(const int &domain,
                                         const int &score)
{
    switch (domain)
    {
        case InputOutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addScore(score);break;
        case CriticalDomain : addScore(score);break;
        case TargetDomain : {
            declareWinner();
            addScore(score);
            break;
        }
        case OutsideDomain : addScore(0);break;
    }
}

DSController *DSController::createInstance()
{
    return new DSController();
}

void DSController::beginInitialize()
{
    emit requestDartsTournamentIndexes(_metaData->tournamentId());
}

void DSController::undoSuccess(const QByteArray& json)
{
    QScopedPointer<DSCContext::IDSCModel> inputModel(_dartsScoreBuilder->createScoreModel(json));
    auto currentTotalScore = addScoreService()->addPlayerScore(inputModel->playerId(),inputModel->score(),scoresService());
    inputModel->setTotalScore(currentTotalScore);
    auto turnValues = _turnValuesBuilder->createTurnValues(_indexService,scoresService(),_scoreLogisticInterface);
    QByteArray jsonResponse = createJsonResponse(inputModel.get(),turnValues);
    emit scoreRemoved(jsonResponse);
}

void DSController::redoSuccess(const QByteArray& json)
{
    auto scoreModel = _dartsScoreBuilder->createScoreModel(json);
    subtractAndAddScoreToModel(scoreModel);
    _indexService->redo();
    auto turnValues = _turnValuesBuilder->createTurnValues(_indexService,scoresService(),
                                                           _scoreLogisticInterface);
    QByteArray jsonResponse = createJsonResponse(scoreModel,turnValues);
    emit scoreAddedSuccess(jsonResponse);
}

void DSController::createAndSendTurnValues(const QByteArray &json)
{
    auto dartsScore = _dartsScoreBuilder->createScoreModel(json);
    auto totalScore = subtractService()->subtractPlayerScore(dartsScore,scoresService());
    dartsScore->setTotalScore(totalScore);
    nextTurn();
    auto turnValues = _turnValuesBuilder->createTurnValues(_indexService,scoresService(), _scoreLogisticInterface);
    QByteArray jsonResponse = createJsonResponse(dartsScore,turnValues);
    emit scoreAddedSuccess(jsonResponse);
}

void DSController::createAndSendWinnerValues()
{
    auto winnerName = _winnerService->winnerName();
    auto winnerId = _winnerService->winnerId();
    auto json = createJsonResponse(winnerId,winnerName);
    emit winnerDeclared(json);
}

void DSController::subtractAndAddScoreToModel(DSCContext::IDSCModel * const scoreModel)
{
    auto newScore = subtractService()->subtractPlayerScore(scoreModel,scoresService());
    scoreModel->setTotalScore(newScore);
}

QByteArray DSController::createJsonResponse(const QUuid &winnerId,const QString &winnerName)
{

    auto json = jsonMerger()->createJsonFromList({jsonBuilder()->createJson(winnerId,"winnerId"),
                                                       jsonBuilder()->createJson(winnerName,"winnerName"),
                                                       jsonBuilder()->createJson(_metaData->tournamentId(),"tournamentId")});
    return json;
}

QByteArray DSController::createJsonResponse(DSCContext::IDSCModel *scoreModel,
                                            const DSCContext::DartsScoreTurnValues *turnValues)
{
    auto jsonResponse = jsonMerger()->createJsonFromList(
                {createJsonFromDSModels()->createJson(scoreModel),turnValues->toJson()}
                );
    return jsonResponse;
}

QByteArray DSController::createJsonResponse(DSCContext::IDSCModel *scoreModel, const DSCContext::IDSCIndexes *indexes,
                                            const DCContext::IDCPlayer *playerModel)
{
    QByteArray json = jsonMerger()->createJsonFromList(
                {
                    jsonBuilder()->createJson(_metaData->tournamentId(),"tournamentId"),
                    createJsonFromDSModels()->createJson(scoreModel),
                    indexes->toJson(),
                    createJsonFromPlayer()->createJson(playerModel)
                });
    return json;
}

void DSController::initializeControllerPlayerDetails(const QByteArray &json)
{
    auto dartsPlayerModels = _playerBuilderService->createModels(json);
    _indexService->setPlayersCount(dartsPlayerModels.count());
    scoresService()->createTuples(dartsPlayerModels,_metaData);
    emit requestTournamentDartsScores(_metaData->tournamentId());
}

void DSController::initializeControllerDartsScores(const QByteArray &json)
{
    auto dartsScores= _dartsScoreBuilder->createScoreModels(json);
    subtractService()->subtractPlayerScore(dartsScores,scoresService());
    emit requestTournamentWinnerIdAndName(_metaData->tournamentId());
}

void DSController::initializeControllerWinnerIdAndName(const QByteArray &json)
{
    auto dartsPlayer = _playerBuilderService->createModel(json);
    _winnerService->setWinner(dartsPlayer->playerId(),dartsPlayer->playerName());
    auto status = _determineControllerStateByWinnerId->service(dartsPlayer->playerId());
    _metaData->setStatus(status);
    emit controllerInitialized(_metaData->displayHint());
}
