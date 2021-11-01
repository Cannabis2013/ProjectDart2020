#include "dartscontroller.h"
void DartsController::createIndexJson()
{
    auto meta = metaBuilder()->buildMeta(metaInfo(),indexController()->index(),scoreModels());
    emit updateTournamentIndex(jsonBuilder()->json(indexController()->index(),meta));
}
void DartsController::handleUserInput(const QByteArray& json)
{
    auto input = inputBuilder()->buildInput(json,playerController(),scoreCalculator(),indexController()->index(),scoreModels());
    input.remainingScoreCand = scoreCalculator()->calculate(indexController()->index(),input.score,scoreModels());
    inputEvaluator()->evaluateInput(input,metaInfo(),this,statusCodes(),playerController());
}
void DartsController::sendTournamentId()
{
    emit sendCurrentTournamentId(metaInfo()->get().tournamentId);
}
void DartsController::createScores()
{
    emit sendDartsScores(jsonBuilder()->json(scoreModels()->scores(),playerStats()->stats()));
}
void DartsController::createScoreJson(const QByteArray &json)
{
    auto input = inputBuilder()->buildInput(json,metaInfo()->get().initialRemainingScore);
    updatePlayerStats()->update(input,playerStats());
    playerController()->updatePlayerStatus(input.playerId,input.inGame);
    auto scoreModel = &scoreModels()->score(input.playerId);
    scoreModel->remainingScore = input.remainingScore;
    emit updatePlayerScore(jsonBuilder()->json(input));
}
void DartsController::reset()
{
    indexController()->initialize();
    scoreModels()->reset(metaInfo()->get().initialRemainingScore);
    playerStats()->reset();
    metaInfo()->get().status = statusCodes()->initialized();
    playerController()->reset();
    emit requestResetTournament(metaInfo()->get().tournamentId);
}
void DartsController::createTurnValuesJson()
{
    auto turnValues = turnValuesBuilder()->turnValues(indexController()->index(),scoreModels(),dartsFinishBuilder());
    emit sendTurnValues(jsonBuilder()->json(turnValues));
}
void DartsController::undoTurn()
{
    auto inputIndex = indexController()->undo(scoreModels()->scores().count());
    auto meta = metaBuilder()->buildMeta(metaInfo(),indexController()->index(),scoreModels());
    auto reqIndex = reqIndexBuilder()->index(indexController()->index());
    emit hideInput(jsonBuilder()->json(reqIndex,inputIndex,meta));
}
void DartsController::redoTurn()
{
    auto meta = metaBuilder()->buildMeta(metaInfo(),indexController()->index(),scoreModels());
    auto index = indexController()->index();
    indexController()->redo(playerController()->count());
    emit revealInput(jsonBuilder()->json(index,meta));
}
void DartsController::persistInput(DCInput &input)
{
    auto index = indexController()->index();
    setInputStats()->set(input,playerStats(),calcMidVal(),index,metaInfo()->get().initialRemainingScore);
    auto meta = metaBuilder()->buildMeta(metaInfo(),index,scoreModels());
    indexController()->next(playerController()->count());
    emit addInputToDbContext(jsonBuilder()->json(input,index,meta));
}
void DartsController::createJsonResponse()
{
    if(metaInfo()->get().status == statusCodes()->winnerFound())
        createWinnerJson();
    else
        createTurnValuesJson();
}
void DartsController::beginInitialize()
{
    emit sendDartsValues(metaInfo()->get().tournamentId);
}
void DartsController::initializeDartsValues(const QByteArray& indexJson, const QByteArray &inputsJson, const QByteArray &playersJson, const QByteArray &winnerJson)
{
    indexController()->initialize(indexBuilder()->index(indexJson));
    DCInitServices::init(playerBuilder()->createPlayers(playersJson),metaInfo()->get(),scoreModels(),scoresBuilder(),playerStats(),playerController());
    DCInitServices::init(inputBuilder()->buildInputs(inputsJson),updatePlayerScores(),updatePlayerStats(),scoreModels(),playerStats());
    DCInitServices::init(playerBuilder()->createWinner(winnerJson),metaInfo()->get(),statusCodes());
    emit initialized(metaInfo()->get().inputHint);
}
void DartsController::requestStatus()
{
    if(metaInfo()->get().status == statusCodes()->winnerFound())
        createWinnerJson();
    else
        emit ready();
}
void DartsController::createWinnerJson()
{
    auto meta = metaBuilder()->buildMeta(metaInfo(),indexController()->index(),scoreModels());
    emit winnerDeclared(jsonBuilder()->json(meta));
}
