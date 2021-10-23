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
    auto input = inputBuilder()->buildInput(json,playerService(),getScoreFromInput(),indexController(),scoreController());
    input.remainingScoreCand = calcRemainingScoreCand()->calc(indexController()->setIndex(),input.score,scoreController());
    inputEvaluator()->evaluateInput(input,playerAllowanceContext(),this);
}
void DartsController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = tournamentId()->id();
    emit sendCurrentTournamentId(tournament);
}
void DartsController::createScores()
{
    auto playerStats = statsController()->playerStats();
    emit sendDartsScores(jsonBuilder()->json(scoreController()->scoreModels(),playerStats));
}
void DartsController::getOrderedInputsWithTotalScores()
{
    emit requestOrderedInputs(tournamentId()->id());
}
void DartsController::userInputAdded(const QByteArray &json)
{
    auto input = inputBuilder()->buildInput(json);
    input.remainingScore = scoreController()->subtractAndUpdate(input).remainingScore;
    indexIterator()->next(indexController(),scoreController());
    auto turnValues = turnValuesBuilder()->turnValues(indexController(),scoreController(),dartsFinishBuilder());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),playerService(),winnerService());
    auto indexes = inputIndexBuilder()->index(indexController());
    emit sendCurrentIndexes(jsonBuilder()->json(input,turnValues,indexes,metaInfo));
}
void DartsController::handleResetTournament()
{
    resetIndexes()->reset(indexController());
    resetScoreModels()->reset(scoreController(),initialScore()->score());
    controllerStatus()->set(statusCodes()->initialized());
    if(playerAllowanceContext() != nullptr)
        playerAllowanceContext()->reset();
    emit requestResetTournament(tournamentId()->id());
}
void DartsController::sendCurrentTurnValues()
{
    auto turnValues = turnValuesBuilder()->turnValues(indexController(),scoreController(),dartsFinishBuilder());
    emit sendTurnValues(jsonBuilder()->json(turnValues));
}
void DartsController::undoTurn()
{
    undoIndex()->undo(indexController(),scoreController());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),playerService(),winnerService());
    auto inputIndex = inputIndexBuilder()->index(indexController());
    auto reqIndex = reqIndexBuilder()->indexes(indexController());
    emit hideInput(jsonBuilder()->json(reqIndex,inputIndex,metaInfo));
}
void DartsController::redoTurn()
{
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),playerService(),winnerService());
    auto jsonResponse = jsonBuilder()->json(inputIndexBuilder()->index(indexController()),metaInfo);
    emit revealInput(jsonResponse);
}
void DartsController::persistInput(DCInput &input)
{
    auto index = inputIndexBuilder()->index(indexController());
    statsController()->updatePlayerStats(input,indexController(),scoreController(),initialScore()->score());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),playerService(),winnerService());
    emit requestAddDartsScore(jsonBuilder()->json(input,index,metaInfo));
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
void DartsController::declareWinner(DCInput &input)
{
    winnerService()->setWinner(input.playerId, input.playerName);
    controllerStatus()->set(statusCodes()->winnerFound());
    persistInput(input);
}
void DartsController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = inputIndexBuilder()->index(json);
    initializeIndexes()->initialize(indexes,indexController());
    emit requestTournamentAssignedPlayerDetails(tournamentId()->id());
}
void DartsController::beginInitialize()
{
    emit requestDartsTournamentIndexes(tournamentId()->id());
}
void DartsController::undoSuccess(const QByteArray& json)
{
    auto input = inputBuilder()->buildInput(json,initialScore()->score());
    scoreController()->updatePlayerRemainingScore(input);
    auto turnValues = turnValuesBuilder()->turnValues(indexController(),scoreController(),dartsFinishBuilder());
    statsController()->updatePlayerStat(input);
    emit scoreRemoved(jsonBuilder()->json(input,turnValues));
}
void DartsController::redoSuccess(const QByteArray& json)
{
    auto input = inputBuilder()->buildInput(json);
    scoreController()->updatePlayerRemainingScore(input);
    statsController()->updatePlayerStat(input);
    indexRedo()->redo(indexController(),scoreController());
    auto turnValues = turnValuesBuilder()->turnValues(indexController(),scoreController(),dartsFinishBuilder());
    emit scoreAddedSuccess(jsonBuilder()->json(input,turnValues));
}
void DartsController::nullifyAndPersistInput(DCInput &input)
{
    input.remainingScore = input.remainingScore + input.score;
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
    statsController()->initialize(players);
    if(playerAllowanceContext() != nullptr)
        playerAllowanceContext()->appendPlayerId(players);
    scoreController()->scoreModels().append(scoreModels);
    emit requestScores(tournamentId()->id());
}
void DartsController::initializePlayerScores(const QByteArray &json)
{
    auto inputs = inputBuilder()->buildInputs(json);
    createCandidatesScore()->update(inputs,statsController(),scoreController());
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
    addTotalScoresToJson()->addRemainingScoreToInputs(modifiedJson,initialScore()->score());
    addPlayerNamesToJson()->addPlayerNamesToJson(modifiedJson,scoreController());
    emit sendOrderedInputs(modifiedJson);
}
