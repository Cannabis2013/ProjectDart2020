#include "dartscontroller.h"
void DartsController::createIndexJson()
{
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winner()->get());
    emit updateTournamentIndex(jsonBuilder()->json(indexController()->index(),metaInfo));
}
void DartsController::handleUserInput(const QByteArray& json)
{
    auto input = inputBuilder()->buildInput(json,playerController(),scoreCalculator(),indexController()->index(),scoreModels());
    input.remainingScoreCand = calcRemainingScoreCand()->calc(indexController()->index(),input.score,scoreModels());
    inputEvaluator()->evaluateInput(input,this,winner(),status(),statusCodes(),playerController());
}
void DartsController::sendTournamentId()
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
void DartsController::createScoreJson(const QByteArray &json)
{
    auto input = inputBuilder()->buildInput(json,initialScore()->score());
    updatePlayerStats()->update(input,playerStats());
    playerController()->updatePlayerStatus(input.playerId,input.inGame);
    auto scoreModel = &scoreModels()->score(input.playerId);
    scoreModel->remainingScore = input.remainingScore;
    emit updatePlayerScore(jsonBuilder()->json(input));
}
void DartsController::reset()
{
    indexController()->initialize();
    scoreModels()->reset(initialScore()->score());
    playerStats()->reset();
    status()->set(statusCodes()->initialized());
    playerController()->reset();
    emit requestResetTournament(tournamentId()->id());
}
void DartsController::createTurnValuesJson()
{
    auto turnValues = turnValuesBuilder()->turnValues(indexController()->index(),scoreModels(),dartsFinishBuilder());
    emit sendTurnValues(jsonBuilder()->json(turnValues));
}
void DartsController::undoTurn()
{
    auto inputIndex = indexController()->undo(scoreModels()->scores().count());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winner()->get());
    auto reqIndex = reqIndexBuilder()->indexes(indexController()->index());
    emit hideInput(jsonBuilder()->json(reqIndex,inputIndex,metaInfo));
}
void DartsController::redoTurn()
{
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winner()->get());
    auto index = indexController()->index();
    indexController()->redo(playerController()->count());
    emit revealInput(jsonBuilder()->json(index,metaInfo));
}
void DartsController::persistInput(DCInput &input)
{
    auto index = indexController()->index();
    input.middle = calcMidVal()->middleValue(indexController()->index(),input.remainingScore,initialScore());
    updateScoreRange()->update(input,playerStats());
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winner()->get());
    indexController()->next(playerController()->count());
    emit addInputToDbContext(jsonBuilder()->json(input,index,metaInfo));
}
void DartsController::createJsonResponse()
{
    if(status()->get() == statusCodes()->winnerFound())
        createWinnerJson();
    else
        createTurnValuesJson();
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
    playerController()->appendPlayerId(players);
    auto inputs = inputBuilder()->buildInputs(inputsJson);
    updatePlayerScores()->update(inputs,scoreModels());
    updatePlayerStats()->update(inputs,playerStats());
    winner()->setWinner(playerBuilder()->createWinner(winnerJson));
    if(winner()->get().id != QUuid())
        status()->set(statusCodes()->winnerFound());
    emit initialized(inputHint()->hint());
}

void DartsController::requestStatus()
{
    if(status()->get() == statusCodes()->winnerFound())
        createWinnerJson();
    else
        emit ready();
}
void DartsController::createWinnerJson()
{
    auto metaInfo = metaBuilder()->buildMeta(tournamentId(),indexController()->index(),scoreModels(),winner()->get());
    emit winnerDeclared(jsonBuilder()->json(metaInfo));
}
