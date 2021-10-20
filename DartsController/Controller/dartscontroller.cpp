#include "dartscontroller.h"
void DartsController::start()
{
    controllerStatus()->set(statusCodes()->awaitsInput());
    sendCurrentTurnValues();
}
void DartsController::stop()
{
    emit controllerIsStopped();
}
void DartsController::handleUserInput(const QByteArray& json)
{
    auto input = inputBuilder()->buildInput(json,playerService(),getScoreFromInput(),indexService(),scoresService());
    auto accumulatedScore = getTotalScore()->scoreCandidate(indexService()->setIndex(),input.score,scoresService());
    inputEvaluator()->evaluateInput(accumulatedScore,input,playerAllowanceContext(),this);
}
void DartsController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = tournamentId()->id();
    emit sendCurrentTournamentId(tournament);
}
void DartsController::createDartsScores()
{
    auto inputs = inputBuilder()->buildInputs(scoresService());
    emit sendDartsScores(jsonBuilder()->json(inputs));
}
void DartsController::getOrderedInputsWithTotalScores()
{
    emit requestOrderedInputs(tournamentId()->id());
}
void DartsController::handleUserInputAdded(const QByteArray &json)
{
    auto input = inputBuilder()->buildInput(json);
    updateTotalScore(input);
    auto stats = statsBuilder()->processScore(input,indexService(),initialScore()->score());
    indexIterator()->next(indexService(),scoresService());
    auto turnValues = turnValuesBuilder()->turnValues(indexService(),scoresService(),dartsFinishBuilder());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),playerService(),winnerService());
    auto indexes = indexesBuilder()->buildIndexes(indexService());
    emit sendCurrentIndexes(jsonBuilder()->json(input,turnValues,indexes,stats,metaInfo));
}
void DartsController::handleResetTournament()
{
    resetIndexes()->reset(indexService());
    resetScoreModels()->reset(scoresService(),initialScore()->score());
    controllerStatus()->set(statusCodes()->initialized());
    if(playerAllowanceContext() != nullptr)
        playerAllowanceContext()->reset();
    emit requestResetTournament(tournamentId()->id());
}
void DartsController::sendCurrentTurnValues()
{
    auto turnValues = turnValuesBuilder()->turnValues(indexService(),scoresService(),dartsFinishBuilder());
    emit awaitsInput(jsonBuilder()->json(turnValues));
}
void DartsController::undoTurn()
{
    undoIndex()->undo(indexService(),scoresService());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),playerService(),winnerService());
    auto jsonResponse = jsonBuilder()->json(indexesBuilder()->buildIndexes(indexService()),metaInfo);
    emit hideInput(jsonResponse);
}
void DartsController::redoTurn()
{
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),playerService(),winnerService());
    auto jsonResponse = jsonBuilder()->json(indexesBuilder()->buildIndexes(indexService()),metaInfo);
    emit revealInput(jsonResponse);
}
void DartsController::persistInput(const DCInput &input)
{
    auto indexes = indexesBuilder()->buildIndexes(indexService());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),playerService(),winnerService());
    auto jsonResponse = jsonBuilder()->json(input,indexes,metaInfo);
    emit requestAddDartsScore(jsonResponse);
}
void DartsController::handleRequestFromUI()
{
    if(controllerStatus()->get() == statusCodes()->winnerFound())
        createAndSendWinnerValues();
    else if(controllerStatus()->get() == statusCodes()->awaitsInput())
        sendCurrentTurnValues();
    else
        emit controllerInitializedAndReady();
}
void DartsController::declareWinner(const DCInput &input)
{
    winnerService()->setWinner(input.playerId, input.playerName);
    controllerStatus()->set(statusCodes()->winnerFound());
    auto indexes = indexesBuilder()->buildIndexes(indexService());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),playerService(),winnerService());
    emit requestAddDartsScore(jsonBuilder()->json(input,indexes,metaInfo));
}
void DartsController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = indexesBuilder()->buildIndexes(json);
    initializeIndexes()->initialize(indexes,indexService());
    emit requestTournamentAssignedPlayerDetails(tournamentId()->id());
}
void DartsController::beginInitialize()
{
    emit requestDartsTournamentIndexes(tournamentId()->id());
}
void DartsController::undoSuccess(const QByteArray& json)
{
    auto input = inputBuilder()->buildInput(json);
    auto turnValues = turnValuesBuilder()->turnValues(indexService(),scoresService(),dartsFinishBuilder());
    input.remainingScore = addScoreService()->addPlayerScore(input, scoresService()).totalScore;
    emit scoreRemoved(jsonBuilder()->json(input,turnValues));
}
void DartsController::redoSuccess(const QByteArray& json)
{
    auto input = inputBuilder()->buildInput(json);
    input.remainingScore = subtractScore()->subtractScore(input,scoresService()).totalScore;
    indexRedo()->redo(indexService(),scoresService());
    auto turnValues = turnValuesBuilder()->turnValues(indexService(),scoresService(),dartsFinishBuilder());
    emit scoreAddedSuccess(jsonBuilder()->json(input,turnValues));
}
void DartsController::updateTotalScore(DCInput &input)
{
    auto candidateScore = createCandidatesScore()->getCandidate(input,scoresService());
    scoresService()->scoreModels().replace(indexService()->setIndex(),candidateScore);
    input.remainingScore = candidateScore.totalScore;
}
void DartsController::nullifyAndPersistInput(DCInput &input)
{
    input.score = 0;
    persistInput(input);
}
void DartsController::createAndSendWinnerValues()
{
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),playerService(),winnerService());
    emit winnerDeclared(jsonBuilder()->json(metaInfo));
}
void DartsController::initializePlayerDetails(const QByteArray &json)
{
    auto players = playerBuilder()->createModels(json);
    auto scoreModels = scoreBuilder()->buildScores(players,initialScore()->score());
    statsBuilder()->setPlayers(players);
    if(playerAllowanceContext() != nullptr)
        playerAllowanceContext()->appendPlayerId(players);
    scoresService()->scoreModels().append(scoreModels);
    emit requestScores(tournamentId()->id());
}
void DartsController::initializeScores(const QByteArray &json)
{
    auto dartsScores = inputBuilder()->buildInputs(json);
    auto candidatesScoreModels = createCandidatesScore()->getScoreCandidates(dartsScores,scoresService());
    updateScoreModels()->update(candidatesScoreModels,scoresService());
    emit requestWinnerDetails(tournamentId()->id());
}
void DartsController::initializeWinnerDetails(const QByteArray &json)
{
    auto winnerModel = winnerModelFromJson()->toWinnerModel(json,playerKeys(),playerBuilder());
    winnerService()->setWinner(winnerModel.id,winnerModel.name);
    controllerStatus()->set(determineStatusById()->status(winnerModel.id,statusCodes()));
    emit initialized(inputHint()->hint(),displayHint()->hint());
}
void DartsController::handleOrderedInputs(const QByteArray &json)
{
    auto modifiedJson = json;
    addTotalScoresToJson()->addTotalScoreToInputs(modifiedJson,initialScore()->score());
    addPlayerNamesToJson()->addPlayerNamesToJson(modifiedJson,scoresService());
    emit sendOrderedInputs(modifiedJson);
}
