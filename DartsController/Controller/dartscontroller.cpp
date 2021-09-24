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
    auto inputModel = createInputModel()->createModel(json,inputKeys());
    auto scoreCandidate = getScoreFromInput()->getScore(inputModel);
    inputModel->setScore(scoreCandidate);
    auto setIndex = indexService()->setIndex();
    auto accumulatedScore = getTotalScore()->scoreCandidate(setIndex,scoreCandidate,scoresService());
    auto domain = inputEvaluator()->validateInput(accumulatedScore,inputKeyCodes(),inputModel->modKeyCode(),inputModel->point());
    processDomain(domain,inputModel);
}

void DartsController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = tournamentId()->id();
    emit sendCurrentTournamentId(tournament);
}

void DartsController::createDartsScores()
{

    auto dartsScoreModels = createInputModels()->createModels(scoresService(),createInputModel());
    auto json = inputsToJson()->createJson(dartsScoreModels);
    emit sendDartsScores(json);
}

void DartsController::getOrderedInputsWithTotalScores()
{
    emit requestOrderedInputs(tournamentId()->id());
}

void DartsController::handleUserInputAdded(const QByteArray &json)
{
    if(metaStatus()->get() == statusCodes()->winnerFound())
        createAndSendWinnerValues();
    else
        updateTotalScore(json);
}

void DartsController::handleResetTournament()
{
    resetIndexes()->reset(indexService());
    resetScoreModels()->reset(scoresService(),initialScore()->score());
    metaStatus()->set(statusCodes()->initialized());
    emit requestResetTournament(tournamentId()->id());
}

void DartsController::sendCurrentTurnValues()
{
    auto model = turnValuesBuilder()->createTurnValues(indexService(),scoresService(),suggestFinishes());
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
    emit hideInput(tournamentId()->id(),currentPlayerId,roundIndex,attemptIndex);
}

void DartsController::redoTurn()
{
    auto activeUser = playerService()->currentPlayerId();
    auto roundIndex = indexService()->roundIndex();
    auto attemptIndex = indexService()->attemptIndex();
    emit revealInput(tournamentId()->id(), activeUser, roundIndex,attemptIndex);
}

void DartsController::addInput(DCContext::IDCInputModel *inputModel)
{
    auto indexes = indexesBuilder()->createIndexes(indexService());
    inputModel->setTournamentId(tournamentId()->id());
    inputModel->setPlayerId(playerService()->currentPlayerId());
    inputModel->setPlayerName(playerService()->currentPlayerName());
    auto json = responseBuilder()->createJsonResponse(inputModel,tournamentId()->id(), inputsToJson(),indexes,indexesToJson());
    emit requestAddDartsScore(json);
}

void DartsController::handleRequestFromUI()
{
    if(metaStatus()->get() == statusCodes()->winnerFound())
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
    metaStatus()->set(statusCodes()->winnerFound());
}

void DartsController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = indexesBuilder()->createIndexes(json);
    initializeIndexes()->initialize(indexes,indexService());
    emit requestTournamentAssignedPlayerDetails(tournamentId()->id());
}

void DartsController::processDomain(const int &domain, DCContext::IDCInputModel *inputModel)
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
    emit requestDartsTournamentIndexes(tournamentId()->id());
}

void DartsController::undoSuccess(const QByteArray& json)
{
    QScopedPointer<DCContext::IDCInputModel> inputModel(createInputModel()->createModel(json,inputKeys()));
    auto tuple = addScoreService()->addPlayerScore(inputModel.get(), scoresService());
    inputModel->setPlayerName(getPlayerName()->playerName(inputModel->playerId(),scoresService()));
    inputModel->setTotalScore(tuple.totalScore);
    auto turnValues = turnValuesBuilder()->createTurnValues(indexService(),scoresService(),suggestFinishes());
    QByteArray jsonResponse = responseBuilder()->createJsonResponse(inputModel.get(), turnValues, inputsToJson(), turnValuesToJson());
    emit scoreRemoved(jsonResponse);
}

void DartsController::redoSuccess(const QByteArray& json)
{
    QScopedPointer<DCContext::IDCInputModel> inputModel(createInputModel()->createModel(json,inputKeys()));
    inputModel->setPlayerName(getPlayerName()->playerName(inputModel->playerId(),scoresService()));
    auto candidateTuple = subtractScore()->subtractScore(inputModel.get(),scoresService());
    inputModel->setTotalScore(candidateTuple.totalScore);
    indexRedo()->redo(indexService(),scoresService());
    auto turnValues = turnValuesBuilder()->createTurnValues(indexService(),scoresService(), suggestFinishes());
    auto jsonResponse = responseBuilder()->createJsonResponse(inputModel.get(),turnValues, inputsToJson(), turnValuesToJson());
    emit scoreAddedSuccess(jsonResponse);
}

void DartsController::updateTotalScore(const QByteArray &json)
{
    QScopedPointer<DCContext::IDCInputModel> inputModel(createInputModel()->createModel(json,inputKeys()));
    auto candidateTuple = createCandidatesTuple()->getCandidate(inputModel.get(),scoresService());
    scoresService()->scoreModels().replace(indexService()->setIndex(),candidateTuple);
    inputModel->setTotalScore(candidateTuple.totalScore);
    nextTurn();
    auto turnValues = turnValuesBuilder()->createTurnValues(indexService(),scoresService(), suggestFinishes());
    auto jsonResponse = responseBuilder()->createJsonResponse(inputModel.get(),turnValues, inputsToJson(), turnValuesToJson());
    emit scoreAddedSuccess(jsonResponse);
}

void DartsController::createAndSendWinnerValues()
{
    auto winnerName = winnerService()->winnerName();
    auto winnerId = winnerService()->winnerId();
    auto json = responseBuilder()->createJsonResponse(winnerId,winnerName,tournamentId()->id());
    emit winnerDeclared(json);
}

void DartsController::initializePlayerDetails(const QByteArray &json)
{
    auto dartsPlayerModels = createPlayersFromJson()->createModels(json,playerKeys(),playerBuilder());
    auto tuples = createScoreTuples()->createTuples(dartsPlayerModels,initialScore()->score());
    scoresService()->scoreModels().append(tuples);
    emit requestScores(tournamentId()->id());
}

void DartsController::initializeScores(const QByteArray &json)
{
    auto dartsScores = createInputModels()->createModels(json,inputKeys(),createInputModel());
    auto candidatesTuples = createCandidatesTuple()->getTupleCandidates(dartsScores,scoresService());
    updateScoreModels()->update(candidatesTuples,scoresService());
    emit requestWinnerDetails(tournamentId()->id());
}

void DartsController::initializeWinnerDetails(const QByteArray &json)
{
    auto winnerModel = winnerModelFromJson()->toWinnerModel(json,winnerKeys(),playerBuilder());
    winnerService()->setWinner(winnerModel->playerId(),winnerModel->playerName());
    auto status = determineStatusById()->status(winnerModel->playerId(),statusCodes());
    metaStatus()->set(status);
    emit initialized(inputHint()->hint(),displayHint()->hint());
}

void DartsController::handleOrderedInputs(const QByteArray &json)
{
    auto modifiedJson = json;
    addTotalScoresToJson()->addTotalScoreToInputs(modifiedJson,initialScore()->score(),inputKeys());
    addPlayerNamesToJson()->addPlayerNamesToJson(modifiedJson,scoresService(),inputKeys());
    emit sendOrderedInputs(modifiedJson);
}
