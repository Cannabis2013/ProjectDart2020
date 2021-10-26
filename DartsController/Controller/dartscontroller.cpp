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
    auto input = inputBuilder()->buildInput(json,getScoreFromInput(),indexController()->index(),scoreModels());
    input.remainingScoreCand = calcRemainingScoreCand()->calc(indexController()->index(),input.score,scoreModels());
    inputEvaluator()->evaluateInput(input,playerAllowanceContext(),this);
}
void DartsController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = tournamentId()->id();
    emit sendCurrentTournamentId(tournament);
}
void DartsController::createScores()
{
    emit sendDartsScores(jsonBuilder()->json(scoreModels()->scores(),playerStats()->stats()));
}
void DartsController::getOrderedInputsWithTotalScores()
{
    emit requestOrderedInputs(tournamentId()->id());
}
void DartsController::userInputAdded(const QByteArray &json)
{
    auto input = inputBuilder()->buildInput(json);
    auto scoreModel = &scoreModels()->score(input.playerId);
    scoreModel->remainingScore -= input.score;
    indexController()->next(scoreModels()->scores().count());
    auto index = indexController()->index();
    auto turnValues = turnValuesBuilder()->turnValues(indexController()->index(),scoreModels(),dartsFinishBuilder());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winnerService());
    emit updateTournamentIndex(jsonBuilder()->json(input,turnValues,index));
}
void DartsController::reset()
{
    indexController()->initialize();
    resetScoreModels()->reset(scoreModels(),initialScore()->score());
    playerStats()->reset();
    controllerStatus()->set(statusCodes()->initialized());
    if(playerAllowanceContext() != nullptr)
        playerAllowanceContext()->reset();
    emit requestResetTournament(tournamentId()->id());
}
void DartsController::sendCurrentTurnValues()
{
    auto turnValues = turnValuesBuilder()->turnValues(indexController()->index(),scoreModels(),dartsFinishBuilder());
    emit sendTurnValues(jsonBuilder()->json(turnValues));
}
void DartsController::undoTurn()
{
    indexController()->undo(scoreModels()->scores().count());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winnerService());
    auto inputIndex = indexController()->index();
    auto reqIndex = reqIndexBuilder()->indexes(indexController()->index());
    emit hideInput(jsonBuilder()->json(reqIndex,inputIndex,metaInfo));
}
void DartsController::redoTurn()
{
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winnerService());
    auto jsonResponse = jsonBuilder()->json(indexController()->index(),metaInfo);
    emit revealInput(jsonResponse);
}
void DartsController::persistInput(DCInput &input)
{
    auto index = indexController()->index();
    updateMiddleValue()->update(input,indexController()->index(),playerStats(),initialScore());
    updateScoreRange()->update(input,playerStats());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winnerService());
    emit addInputToDbContext(jsonBuilder()->json(input,index,metaInfo));
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
    indexController()->initialize(indexBuilder()->index(json));
    emit requestTournamentAssignedPlayerDetails(tournamentId()->id());
}
void DartsController::beginInitialize()
{
    emit requestDartsTournamentIndexes(tournamentId()->id());
}
void DartsController::undoSuccess(const QByteArray& json)
{
    auto input = inputBuilder()->buildInput(json,initialScore()->score());
    auto scoreModel = &scoreModels()->score(input.playerId);
    scoreModel->remainingScore = input.remainingScore;
    auto turnValues = turnValuesBuilder()->turnValues(indexController()->index(),scoreModels(),dartsFinishBuilder());
    updatePlayerStats()->update(input,playerStats());
    emit scoreRemoved(jsonBuilder()->json(input,turnValues));
}
void DartsController::redoSuccess(const QByteArray& json)
{
    auto input = inputBuilder()->buildInput(json);
    auto scoreModel = &scoreModels()->score(input.playerId);
    scoreModel->remainingScore = input.remainingScore;
    updatePlayerStats()->update(input,playerStats());
    indexController()->redo(scoreModels()->scores().count());
    auto turnValues = turnValuesBuilder()->turnValues(indexController()->index(),scoreModels(),dartsFinishBuilder());
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
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winnerService());
    emit winnerDeclared(jsonBuilder()->json(metaInfo));
}
void DartsController::initializePlayerDetails(const QByteArray &json)
{
    auto players = playerBuilder()->createPlayers(json);
    auto scores = scoresBuilder()->createScores(players,initialScore()->score());
    playerStats()->setPlayers(players);
    if(playerAllowanceContext() != nullptr)
        playerAllowanceContext()->appendPlayerId(players);
    scoreModels()->scores().append(scores);
    emit requestScores(tournamentId()->id());
}
void DartsController::initializePlayerScores(const QByteArray &json)
{
    auto inputs = inputBuilder()->buildInputs(json);
    updatePlayerScores()->update(inputs,scoreModels());
    updatePlayerStats()->update(inputs,playerStats());
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
    addPlayerNamesToJson()->addPlayerNamesToJson(modifiedJson,scoreModels());
    emit sendOrderedInputs(modifiedJson);
}
