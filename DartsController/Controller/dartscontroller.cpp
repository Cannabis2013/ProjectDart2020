#include "dartscontroller.h"
void DartsController::createIndexJson()
{
    auto meta = createMeta()->create(metaInfo(),indexController()->index(),scoreModels());
    auto future = modelsContext()->updateTournamentIndex(createJson()->create(indexController()->index(),meta));
    Runnable::run([=]{
        if(future.result())
            createJsonResponse();
    },future);
}
void DartsController::handleUserInput(const QByteArray& json)
{
    auto input = createInput()->create(json,playerController(),scoreCalculator(),indexController()->index(),scoreModels());
    input.remainingScoreCand = scoreCalculator()->calculate(indexController()->index(),input.score,scoreModels());
    evaluateInput()->evaluate(input,metaInfo(),this,statusCodes(),playerController());
}
void DartsController::sendTournamentId()
{
    emit sendCurrentTournamentId(metaInfo()->get().tournamentId);
}
void DartsController::createScores()
{
    emit sendDartsScores(createJson()->create(scoreModels()->scores(),playerStats()->stats()));
}
void DartsController::reset()
{
    indexController()->init();
    scoreModels()->reset(metaInfo()->get().initialRemainingScore);
    playerStats()->reset();
    metaInfo()->get().status = statusCodes()->initialized();
    playerController()->reset();
    auto future = modelsContext()->resetTournament(metaInfo()->get().tournamentId);
    Runnable::run([=]{
        if(future.result())
            emit resetSucces();
    },future);
}
void DartsController::createTurnValuesJson()
{
    auto values = turnValuesBuilder()->turnValues(indexController()->index(),scoreModels(),dartsFinishBuilder());
    emit sendTurnValues(createJson()->create(values));
}
void DartsController::updateScoreDetails(const QByteArray &json)
{
    auto input = createInput()->create(json,metaInfo()->get().initialRemainingScore);
    updatePlayerStats()->update(input,playerStats());
    playerController()->updateStatus(input.playerId,input.inGame);
    auto scoreModel = &scoreModels()->score(input.playerId);
    scoreModel->remainingScore = input.remainingScore;
    emit updatePlayerScore(createJson()->create(input));
}
void DartsController::undoTurn()
{
    auto inputIndex = indexController()->undo(scoreModels()->scores().count());
    auto meta = createMeta()->create(metaInfo(),indexController()->index(),scoreModels());
    auto reqIndex = reqIndexBuilder()->index(indexController()->index());
    auto undoJson = createJson()->create(reqIndex,inputIndex,meta);
    auto future = modelsContext()->hideInput(undoJson);
    Runnable::run([=]{updateScoreDetails(future.result());},future);
}
void DartsController::redoTurn()
{
    auto meta = createMeta()->create(metaInfo(),indexController()->index(),scoreModels());
    auto index = indexController()->index();
    indexController()->redo(playerController()->count());
    auto json = createJson()->create(index,meta);
    auto future = modelsContext()->revealInput(json);
    Runnable::run([=]{updateScoreDetails(future.result());},future);
}
void DartsController::persistInput(DCInput &input)
{
    auto index = indexController()->index();
    setInputStats()->set(input,playerStats(),calcMidVal(),index,metaInfo()->get().initialRemainingScore);
    auto meta = createMeta()->create(metaInfo(),index,scoreModels());
    indexController()->next(playerController()->count());
    auto json = createJson()->create(input,index,meta);
    auto future = modelsContext()->addInput(json);
    Runnable::run([=]{updateScoreDetails(future.result());},future);
}
void DartsController::createJsonResponse()
{
    if(metaInfo()->get().status == statusCodes()->winnerFound())
        createWinnerJson();
    else
        createTurnValuesJson();
}
void DartsController::initialize()
{
    JsonExtractor extractor(modelsContext()->createDartsValuesJson(metaInfo()->get().tournamentId));
    DCInit::init(playerBuilder()->createPlayers(extractor.toArray("players")), metaInfo()->get(),scoreModels(),scoresBuilder(),playerStats(),playerController());
    indexController()->init(indexBuilder()->index(extractor.toObject("index")));
    DCInit::init(createInput()->buildInputs(extractor.toArray("inputs")),updatePlayerScores(),updatePlayerStats(),scoreModels(),playerStats());
    DCInit::init(playerBuilder()->createWinner(extractor.toObject("winnerDetails")),metaInfo()->get(),statusCodes());
    emit initialized();
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
    auto meta = createMeta()->create(metaInfo(),indexController()->index(),scoreModels());
    emit winnerDeclared(createJson()->create(meta));
}
