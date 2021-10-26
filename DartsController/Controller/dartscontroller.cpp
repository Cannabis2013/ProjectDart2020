#include "dartscontroller.h"
void DartsController::start()
{
    status()->set(statusCodes()->awaitsInput());
    sendCurrentTurnValues();
}
void DartsController::handleUserInput(const QByteArray& json)
{
    auto input = inputBuilder()->buildInput(json,scoreCalculator(),indexController()->index(),scoreModels());
    input.remainingScoreCand = calcRemainingScoreCand()->calc(indexController()->index(),input.score,scoreModels());
    inputEvaluator()->evaluateInput(input,this,winner(),status(),statusCodes(),playerController());
}
void DartsController::handleRequestForCurrentTournamentMetaData()
{
    emit sendCurrentTournamentId(tournamentId()->id());
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
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winner()->winner());
    emit updateTournamentIndex(jsonBuilder()->json(input,turnValues,index));
}
void DartsController::reset()
{
    indexController()->initialize();
    scoreModels()->reset(initialScore()->score());
    playerStats()->reset();
    status()->set(statusCodes()->initialized());
    if(playerController() != nullptr)
        playerController()->reset();
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
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winner()->winner());
    auto inputIndex = indexController()->index();
    auto reqIndex = reqIndexBuilder()->indexes(indexController()->index());
    emit hideInput(jsonBuilder()->json(reqIndex,inputIndex,metaInfo));
}
void DartsController::redoTurn()
{
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winner()->winner());
    emit revealInput(jsonBuilder()->json(indexController()->index(),metaInfo));
}
void DartsController::persistInput(DCInput &input)
{
    auto index = indexController()->index();
    updateMiddleValue()->update(input,indexController()->index(),playerStats(),initialScore());
    updateScoreRange()->update(input,playerStats());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winner()->winner());
    emit addInputToDbContext(jsonBuilder()->json(input,index,metaInfo));
}
void DartsController::handleRequestFromUI()
{
    if(status()->get() == statusCodes()->winnerFound())
        createAndSendWinnerValues();
    else if(status()->get() == statusCodes()->awaitsInput())
        sendCurrentTurnValues();
    else
        emit controllerInitializedAndReady();
}
void DartsController::beginInitialize()
{
    emit sendDartsValues(tournamentId()->id());
}
void DartsController::initializeDartsValues(const QByteArray& indexJson, const QByteArray &inputsJson, const QByteArray &playersJson, const QByteArray &winnerJson)
{
    indexController()->initialize(indexBuilder()->index(indexJson));
    auto players = playerBuilder()->createPlayers(playersJson);
    scoreModels()->scores().append(scoresBuilder()->createScores(players,initialScore()->score()));
    playerStats()->setPlayers(players);
    if(playerController() != nullptr)
        playerController()->appendPlayerId(players);
    auto inputs = inputBuilder()->buildInputs(inputsJson);
    updatePlayerScores()->update(inputs,scoreModels());
    updatePlayerStats()->update(inputs,playerStats());
    winner()->setWinner(playerBuilder()->createWinner(winnerJson));
    status()->set(determineStatusById()->status(winner()->winner().id,statusCodes()));
    emit initialized(inputHint()->hint());
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
void DartsController::createAndSendWinnerValues()
{
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winner()->winner());
    emit winnerDeclared(jsonBuilder()->json(metaInfo));
}
