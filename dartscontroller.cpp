#include "dartscontroller.h"

void DartsController::start()
{
    sendCurrentTurnValues();
}

void DartsController::stop()
{
    emit controllerIsStopped();
}

void DartsController::handleUserInput(const QByteArray& json)
{
    auto inputModel = inputModelBuilder()->createModel(json,jsonExtractor());
    auto scoreCandidate = getScoreFromInput()->getScore(inputModel);
    inputModel->setScore(scoreCandidate);
    auto setIndex = indexService()->setIndex();
    auto accumulatedScore = getTotalScore()->scoreCandidate(setIndex,scoreCandidate,scoresService());
    auto domain = inputEvaluator()->validateInput(accumulatedScore,inputModel->modKeyCode(),inputModel->point());
    processDomain(domain,inputModel);
}

void DartsController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = metaData()->tournamentId();
    emit sendCurrentTournamentId(tournament);
}

void DartsController::createDartsScores()
{
    auto dartsScoreModels = inputModelBuilder()->createModels(scoresService());
    auto json = inputsToJson()->createJson(dartsScoreModels);
    emit sendDartsScores(json);
}

void DartsController::getOrderedInputsWithTotalScores()
{
    auto tournamentId = metaData()->tournamentId();
    emit requestOrderedInputs(tournamentId);
}

void DartsController::handleUserInputAdded(const QByteArray &json)
{
    if(metaData()->status() == WinnerDeclared)
        createAndSendWinnerValues();
    else
        updateTotalScore(json);
}

void DartsController::handleResetTournament()
{
    resetIndexes()->reset(indexService());
    scoresService()->resetTuples(metaData());
    auto tournamentId = metaData()->tournamentId();
    emit requestResetTournament(tournamentId);
}

void DartsController::sendCurrentTurnValues()
{
    auto model = turnValuesBuilder()->createTurnValues(indexService(),scoresService(),scoreLogisticInterface());
    emit awaitsInput(turnValuesToJson()->create(model));
}

int DartsController::lastPlayerIndex()
{
    auto playerCount = scoresService()->scoreModels().count();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}

void DartsController::undoTurn()
{
    undoIndex()->undo(indexService(),scoresService());
    auto roundIndex = indexService()->roundIndex();
    auto attemptIndex = indexService()->attemptIndex();
    auto currentPlayerId = playerService()->currentPlayerId();
    emit hideInput(metaData()->tournamentId(),currentPlayerId,roundIndex,attemptIndex);
}

void DartsController::redoTurn()
{
    auto activeUser = playerService()->currentPlayerId();
    auto roundIndex = indexService()->roundIndex();
    auto attemptIndex = indexService()->attemptIndex();
    emit revealInput(metaData()->tournamentId(), activeUser, roundIndex,attemptIndex);
}

void DartsController::addInput(DCContext::IDCModel *inputModel)
{
    auto indexes = indexesBuilder()->createIndexes(indexService());
    inputModel->setTournamentId(metaData()->tournamentId());
    inputModel->setPlayerId(playerService()->currentPlayerId());
    inputModel->setPlayerName(playerService()->currentPlayerName());
    auto json = responseBuilder()->createJsonResponse(inputModel,metaData()->tournamentId(), inputsToJson(),indexes,indexesToJson());
    emit requestAddDartsScore(json);
}

void DartsController::handleRequestFromUI()
{
    if(metaData()->status() == ControllerState::WinnerDeclared)
        createAndSendWinnerValues();
    else
        emit controllerInitializedAndReady();
}

void DartsController::nextTurn()
{
    indexIterator()->next(indexService(),scoresService());
    sendCurrentTurnValues();
}

void DartsController::declareWinner()
{
    auto currentPlayerId = playerService()->currentPlayerId();
    auto currentPlayerName = playerService()->currentPlayerName();
    winnerService()->setWinner(currentPlayerId, currentPlayerName);
    metaData()->setStatus(ControllerState::WinnerDeclared);
}

void DartsController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = indexesBuilder()->createIndexes(json);
    initializeIndexes()->initialize(indexes,indexService());
    emit requestTournamentAssignedPlayerDetails(metaData()->tournamentId());
}

void DartsController::processDomain(const int &domain, DCContext::IDCModel *inputModel)
{
    switch (domain)
    {
        case InputOutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addInput(inputModel);break;
        case CriticalDomain : addInput(inputModel);break;
        case TargetDomain : {
            declareWinner();
            addInput(inputModel);
            break;
        }
        case OutsideDomain : {
            inputModel->setScore(0);
            addInput(inputModel);
            break;
        }
    }
}

void DartsController::beginInitialize()
{
    emit requestDartsTournamentIndexes(metaData()->tournamentId());
}

void DartsController::undoSuccess(const QByteArray& json)
{
    QScopedPointer<DCContext::IDCModel> inputModel(inputModelBuilder()->createModel(json,jsonExtractor()));
    auto tuple = addScoreService()->addPlayerScore(inputModel.get(), scoresService());
    inputModel->setPlayerName(getPlayerName()->playerName(inputModel->playerId(),scoresService()));
    inputModel->setTotalScore(tuple.totalScore);
    auto turnValues = turnValuesBuilder()->createTurnValues(indexService(),scoresService(),scoreLogisticInterface());
    QByteArray jsonResponse = responseBuilder()->createJsonResponse(inputModel.get(), turnValues, inputsToJson(), turnValuesToJson());
    emit scoreRemoved(jsonResponse);
}

void DartsController::redoSuccess(const QByteArray& json)
{
    QScopedPointer<DCContext::IDCModel> inputModel(inputModelBuilder()->createModel(json,jsonExtractor()));
    inputModel->setPlayerName(getPlayerName()->playerName(inputModel->playerId(),scoresService()));
    auto candidateTuple = subtractScore()->subtractScore(inputModel.get(),scoresService());
    inputModel->setTotalScore(candidateTuple.totalScore);
    indexRedo()->redo(indexService(),scoresService());
    auto turnValues = turnValuesBuilder()->createTurnValues(indexService(),scoresService(), scoreLogisticInterface());
    auto jsonResponse = responseBuilder()->createJsonResponse(inputModel.get(),turnValues, inputsToJson(), turnValuesToJson());
    emit scoreAddedSuccess(jsonResponse);
}

void DartsController::updateTotalScore(const QByteArray &json)
{
    QScopedPointer<DCContext::IDCModel> inputModel(inputModelBuilder()->createModel(json,jsonExtractor()));
    auto candidateTuple = createCandidatesTuple()->getCandidate(inputModel.get(),scoresService());
    scoresService()->scoreModels().replace(indexService()->setIndex(),candidateTuple);
    inputModel->setTotalScore(candidateTuple.totalScore);
    nextTurn();
    auto turnValues = turnValuesBuilder()->createTurnValues(indexService(),scoresService(), scoreLogisticInterface());
    auto jsonResponse = responseBuilder()->createJsonResponse(inputModel.get(),turnValues, inputsToJson(), turnValuesToJson());
    emit scoreAddedSuccess(jsonResponse);
}

void DartsController::createAndSendWinnerValues()
{
    auto winnerName = winnerService()->winnerName();
    auto winnerId = winnerService()->winnerId();
    auto json = responseBuilder()->createJsonResponse(winnerId,winnerName,metaData()->tournamentId());
    emit winnerDeclared(json);
}

void DartsController::initializePlayerDetails(const QByteArray &json)
{
    auto dartsPlayerModels = playerBuilder()->createModels(json);
    auto tuples = createScoreTuples()->createTuples(dartsPlayerModels,metaData());
    scoresService()->scoreModels().append(tuples);
    emit requestScores(metaData()->tournamentId());
}

void DartsController::initializeScores(const QByteArray &json)
{
    auto dartsScores = inputModelBuilder()->createModels(json,jsonExtractor());
    auto candidatesTuples = createCandidatesTuple()->getTupleCandidates(dartsScores,scoresService());
    updateScoreTuples()->update(candidatesTuples,scoresService());
    emit requestWinnerDetails(metaData()->tournamentId());
}

void DartsController::initializeWinnerDetails(const QByteArray &json)
{
    auto dartsPlayer = playerBuilder()->createModel(json);
    winnerService()->setWinner(dartsPlayer->playerId(),dartsPlayer->playerName());
    auto status = determineControllerStateByWinnerId()->service(dartsPlayer->playerId());
    metaData()->setStatus(status);
    emit initialized(metaData()->inputHint(),metaData()->displayHint());
}

void DartsController::handleOrderedInputs(const QByteArray &json)
{
    auto modifiedJson = json;
    addTotalScoresToJson()->addTotalScoreToInputs(modifiedJson,metaData()->initialScore());
    addPlayerNamesToJson()->addPlayerNamesToJson(modifiedJson,scoresService());
    emit sendOrderedInputs(modifiedJson);
}
