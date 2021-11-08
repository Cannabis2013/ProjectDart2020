#include "dartscontroller.h"
void DartsController::createIndexJson()
{
    auto meta = createMeta()->create(getMetaInfo(),indexController()->index(),scoreModels());
    emit updateTournamentIndex(createJson()->create(indexController()->index(),meta));
}
void DartsController::handleUserInput(const QByteArray& json)
{
    auto input = createInput()->create(json,playerController(),scoreCalculator(),indexController()->index(),scoreModels());
    input.remainingScoreCand = scoreCalculator()->calculate(indexController()->index(),input.score,scoreModels());
    evaluateInput()->evaluate(input,getMetaInfo(),this,statusCodes(),playerController());
}
void DartsController::sendTournamentId()
{
    emit sendCurrentTournamentId(getMetaInfo()->get().tournamentId);
}
void DartsController::createScores()
{
    emit sendDartsScores(createJson()->create(scoreModels()->scores(),playerStats()->stats()));
}
void DartsController::createScoreJson(const QByteArray &json)
{
    auto input = createInput()->create(json,getMetaInfo()->get().initialRemainingScore);
    updatePlayerStats()->update(input,playerStats());
    playerController()->updateStatus(input.playerId,input.inGame);
    auto scoreModel = &scoreModels()->score(input.playerId);
    scoreModel->remainingScore = input.remainingScore;
    emit updatePlayerScore(createJson()->create(input));
}
void DartsController::reset()
{
    indexController()->init();
    scoreModels()->reset(getMetaInfo()->get().initialRemainingScore);
    playerStats()->reset();
    getMetaInfo()->get().status = statusCodes()->initialized();
    playerController()->reset();
    emit requestResetTournament(getMetaInfo()->get().tournamentId);
}
void DartsController::createTurnValuesJson()
{
    auto turnValues = turnValuesBuilder()->turnValues(indexController()->index(),scoreModels(),dartsFinishBuilder());
    emit sendTurnValues(createJson()->create(turnValues));
}
void DartsController::undoTurn()
{
    auto inputIndex = indexController()->undo(scoreModels()->scores().count());
    auto meta = createMeta()->create(getMetaInfo(),indexController()->index(),scoreModels());
    auto reqIndex = reqIndexBuilder()->index(indexController()->index());
    emit hideInput(createJson()->create(reqIndex,inputIndex,meta));
}
void DartsController::redoTurn()
{
    auto meta = createMeta()->create(getMetaInfo(),indexController()->index(),scoreModels());
    auto index = indexController()->index();
    indexController()->redo(playerController()->count());
    emit revealInput(createJson()->create(index,meta));
}
void DartsController::persistInput(DCInput &input)
{
    auto index = indexController()->index();
    setInputStats()->set(input,playerStats(),calcMidVal(),index,getMetaInfo()->get().initialRemainingScore);
    auto meta = createMeta()->create(getMetaInfo(),index,scoreModels());
    indexController()->next(playerController()->count());
    emit addInputToDbContext(createJson()->create(input,index,meta));
}
void DartsController::createJsonResponse()
{
    if(getMetaInfo()->get().status == statusCodes()->winnerFound())
        createWinnerJson();
    else
        createTurnValuesJson();
}
void DartsController::startInit()
{
    emit sendInitValues(getMetaInfo()->get().tournamentId);
}
void DartsController::init(const QByteArray& indexJson, const QByteArray &inputsJson, const QByteArray &playersJson, const QByteArray &winnerJson)
{
    indexController()->init(indexBuilder()->index(indexJson));
    DCInitServices::init(playerBuilder()->createPlayers(playersJson),getMetaInfo()->get(),scoreModels(),scoresBuilder(),playerStats(),playerController());
    DCInitServices::init(createInput()->buildInputs(inputsJson),updatePlayerScores(),updatePlayerStats(),scoreModels(),playerStats());
    DCInitServices::init(playerBuilder()->createWinner(winnerJson),getMetaInfo()->get(),statusCodes());
    emit initialized(getMetaInfo()->get().inputHint);
}
void DartsController::requestStatus()
{
    if(getMetaInfo()->get().status == statusCodes()->winnerFound())
        createWinnerJson();
    else
        emit ready();
}
void DartsController::createWinnerJson()
{
    auto meta = createMeta()->create(getMetaInfo(),indexController()->index(),scoreModels());
    emit winnerDeclared(createJson()->create(meta));
}
