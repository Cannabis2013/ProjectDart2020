#include "dartscontroller.h"

void DartsController::start()
{
    sendCurrentTurnValues();
}

void DartsController::stop()
{
    emit controllerIsStopped();
}

void DartsController::handleAndProcessUserInput(const QByteArray& json)
{
    auto inputModel = jsonToInputModel()->toModel(json);
    auto scoreCandidate = calculateScore()->getScore(inputModel);
    auto setIndex = _indexService->setIndex();
    auto accumulatedScore = calcAccScoreCand()->scoreCandidate(setIndex,scoreCandidate,scoresService());
    auto domain = _inputEvaluator->validateInput(accumulatedScore);
    processDomain(domain,scoreCandidate);
}

void DartsController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = _metaData->tournamentId();
    emit sendCurrentTournamentId(tournament);
}

void DartsController::createOrderedDartsScores()
{
    auto dartsScoreModels = inputModelBuilder()->createModels(scoresService());
    auto json = createJsonFromDSModels()->createJson(dartsScoreModels);
    emit sendDartsScores(json);
}

void DartsController::handleRequestDartsScores()
{
    auto tournamentId = _metaData->tournamentId();
    emit requestDartsScores(tournamentId);
}

void DartsController::handleScoreAddedToDataContext(const QByteArray &json)
{
    if(_metaData->status() == WinnerDeclared)
        createAndSendWinnerValues();
    else
        updateTotalScore(json);
}

void DartsController::handleResetTournament()
{
    _indexService->reset();
    scoresService()->resetTuples(_metaData);
    auto tournamentId = _metaData->tournamentId();
    emit requestResetTournament(tournamentId);
}

void DartsController::sendCurrentTurnValues()
{
    auto model = turnValuesBuilder()->createTurnValues(_indexService,scoresService(),_scoreLogisticInterface);
    emit awaitsInput(turnValuesToJson()->create(model));
}

QString DartsController::currentPlayerName()
{
    auto index = _indexService->setIndex();
    auto playerName = scoresService()->tuples().at(index).name;
    return playerName;
}

QUuid DartsController::currentPlayerId()
{
    auto index = _indexService->setIndex();
    auto playerID = scoresService()->tuples().at(index).id;
    return playerID;
}

int DartsController::lastPlayerIndex()
{
    auto playerCount = scoresService()->tuples().count();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


void DartsController::undoTurn()
{
    if(_metaData->status() == ControllerState::WinnerDeclared)
        return;
    _indexService->undo();
    auto roundIndex = _indexService->roundIndex();
    auto attemptIndex = _indexService->attemptIndex();
    emit hideInput(_metaData->tournamentId(),currentPlayerId(),roundIndex,attemptIndex);
}

void DartsController::redoTurn()
{
    auto activeUser = currentPlayerId();
    auto roundIndex = _indexService->roundIndex();
    auto attemptIndex = _indexService->attemptIndex();
    emit revealInput(_metaData->tournamentId(), activeUser, roundIndex,attemptIndex);
}

void DartsController::addScore(const int& score)
{
    auto indexes = indexesBuilder()->createIndexes(_indexService);
    auto inputModel = inputModelBuilder()->createModel(score);
    auto playerModel = playerBuilder()->createModel(currentPlayerId(),currentPlayerName());
    auto json = createJsonResponse(inputModel,indexes,playerModel);
    emit requestAddDartsScore(json);
}

void DartsController::handleRequestFromUI()
{
    if(_metaData->status() == ControllerState::WinnerDeclared)
        createAndSendWinnerValues();
    else
        emit controllerInitializedAndReady();
}

void DartsController::nextTurn()
{
    _indexService->next();
    sendCurrentTurnValues();
}

void DartsController::declareWinner()
{
    _winnerService->setWinner(currentPlayerId(), currentPlayerName());
    _metaData->setStatus(ControllerState::WinnerDeclared);
}

void DartsController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = indexesBuilder()->createIndexes(json);
    initializeIndexes()->initialize(indexes,_indexService);
    emit requestTournamentAssignedPlayerDetails(_metaData->tournamentId());
}

void DartsController::processDomain(const int &domain, const int &score)
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

DartsController *DartsController::createInstance()
{
    return new DartsController();
}

void DartsController::beginInitialize()
{
    emit requestDartsTournamentIndexes(_metaData->tournamentId());
}

void DartsController::undoSuccess(const QByteArray& json)
{
    QScopedPointer<DCContext::IDCModel> inputModel(inputModelBuilder()->createModel(json));
    auto currentTotalScore = addScoreService()->addPlayerScore(inputModel->playerId(),inputModel->score(),scoresService());
    inputModel->setTotalScore(currentTotalScore);
    auto turnValues = turnValuesBuilder()->createTurnValues(_indexService,scoresService(),_scoreLogisticInterface);
    QByteArray jsonResponse = createJsonResponse(inputModel.get(),turnValues);
    emit scoreRemoved(jsonResponse);
}

void DartsController::redoSuccess(const QByteArray& json)
{
    auto inputModel = inputModelBuilder()->createModel(json);
    auto candidateTuple = createCandidatesTuple()->getCandidate(inputModel,scoresService());
    inputModel->setTotalScore(candidateTuple.totalScore);
    _indexService->redo();
    auto turnValues = turnValuesBuilder()->createTurnValues(_indexService,scoresService(),
                                                           _scoreLogisticInterface);
    QByteArray jsonResponse = createJsonResponse(inputModel,turnValues);
    emit scoreAddedSuccess(jsonResponse);
}

void DartsController::updateTotalScore(const QByteArray &json)
{
    auto dartsScore = inputModelBuilder()->createModel(json);
    auto candidateTuple = createCandidatesTuple()->getCandidate(dartsScore,scoresService());
    dartsScore->setTotalScore(candidateTuple.totalScore);
    nextTurn();
    auto turnValues = turnValuesBuilder()->createTurnValues(_indexService,scoresService(), _scoreLogisticInterface);
    QByteArray jsonResponse = createJsonResponse(dartsScore,turnValues);
    emit scoreAddedSuccess(jsonResponse);
}

void DartsController::createAndSendWinnerValues()
{
    auto winnerName = _winnerService->winnerName();
    auto winnerId = _winnerService->winnerId();
    auto json = createJsonResponse(winnerId,winnerName);
    emit winnerDeclared(json);
}

QByteArray DartsController::createJsonResponse(const QUuid &winnerId,const QString &winnerName)
{

    auto json = JsonMerger::createJsonFromList({jsonGenericBuilder()->createJson(winnerId,"winnerId"),
                                                jsonGenericBuilder()->createJson(winnerName,"winnerName"),
                                                jsonGenericBuilder()->createJson(_metaData->tournamentId(),"tournamentId")});
    return json;
}

QByteArray DartsController::createJsonResponse(DCContext::IDCModel *inputModel,
                                               const DCContext::DCTurnValues *turnValues)
{
    auto jsonResponse = JsonMerger::createJsonFromList(
                {
                    createJsonFromDSModels()->createJson(inputModel),
                    turnValuesToJson()->create(turnValues)
                });
    return jsonResponse;
}

QByteArray DartsController::createJsonResponse(DCContext::IDCModel *inputModel,
                                               const DCContext::IDCIndexes *indexes,
                                               const DCContext::IDCPlayer *playerModel)
{
    QByteArray json = JsonMerger::createJsonFromList(
                {
                    jsonGenericBuilder()->createJson(_metaData->tournamentId(),"tournamentId"),
                    createJsonFromDSModels()->createJson(inputModel),
                    indexesToJson()->toJson(indexes),
                    createJsonFromPlayer()->createJson(playerModel)
                });
    return json;
}

void DartsController::initializePlayerDetails(const QByteArray &json)
{
    auto dartsPlayerModels = playerBuilder()->createModels(json);
    _indexService->setPlayersCount(dartsPlayerModels.count());
    auto tuples = createScoreTuples()->createTuples(dartsPlayerModels,_metaData);
    scoresService()->tuples().append(tuples);
    emit requestTournamentDartsScores(_metaData->tournamentId());
}

void DartsController::initializeDartsScores(const QByteArray &json)
{
    auto dartsScores = inputModelBuilder()->createModels(json);
    auto candidatesTuples = createCandidatesTuple()->getTupleCandidates(dartsScores,scoresService());
    replaceTuples()->replace(candidatesTuples,scoresService());
    emit requestTournamentWinnerIdAndName(_metaData->tournamentId());
}

void DartsController::initializeWinnerDetails(const QByteArray &json)
{
    auto dartsPlayer = playerBuilder()->createModel(json);
    _winnerService->setWinner(dartsPlayer->playerId(),dartsPlayer->playerName());
    auto status = determineControllerStateByWinnerId()->service(dartsPlayer->playerId());
    _metaData->setStatus(status);
    emit controllerInitialized(_metaData->displayHint());
}
