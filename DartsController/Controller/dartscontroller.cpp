#include "dartscontroller.h"
void DartsController::handleUserInput(const QByteArray& json)
{
    auto input = createInput()->create(json,playerController(),scoreCalculator(),indexController()->index(),scoreModels());
    auto scoreCand = scoreCalculator()->calculate(indexController()->index(),input->score(),scoreModels());
    evaluateInput()->evaluate(input,scoreCand,metaInfo(),this,statusCodes(),playerController());
}
QByteArray DartsController::getPlayerScores()
{
    return createJson()->create(scoreModels()->scores(),playerStats()->stats());
}
void DartsController::reset()
{
    indexController()->init();
    scoreModels()->reset(metaInfo()->get().initialRemainingScore);
    playerStats()->reset();
    metaInfo()->get().status = statusCodes()->initialized();
    playerController()->reset();
    auto future = modelsContext()->resetTournament(metaInfo()->get().tournamentId);
    RunLater::run([=]{if(future.result())emit resetSucces();},future);
}
QByteArray DartsController::createTurnValuesJson()
{
    auto turnValues = turnValuesBuilder()->turnValues(indexController()->index(),scoreModels(),dartsFinishBuilder());
    return createJson()->create(turnValues);
}
void DartsController::updateScoreDetails(AbstractDartsInput *input)
{
    updatePlayerStats()->update(input,playerStats());
    playerController()->updateStatus(input->playerId(),input->inGame());
    auto scoreModel = &scoreModels()->score(input->playerId());
    scoreModel->remainingScore = input->remainingScore();
    emit updatePlayerScore(createJson()->create(input));
}
void DartsController::undoTurn()
{
    auto inputIndex = indexController()->undo(scoreModels()->scores().count());
    auto meta = createMeta()->create(metaInfo(),indexController()->index(),scoreModels());
    auto reqIndex = reqIndexBuilder()->index(indexController()->index(),indexBuilder());
    auto future = modelsContext()->hideInput(meta.tournamentId,meta.currentPlayerId,inputIndex);
    RunLater::run([=]{
        auto input = modelsContext()->input(meta.tournamentId,meta.currentPlayerId,reqIndex);
        updateScoreDetails(input);
    },future);
}
void DartsController::redoTurn()
{
    auto meta = createMeta()->create(metaInfo(),indexController()->index(),scoreModels());
    auto index = indexController()->index();
    indexController()->redo(playerController()->count());
    auto future = modelsContext()->revealInput(meta.tournamentId,meta.currentPlayerId,index);
    RunLater::run([=]{
        if(future.result())
        {
            auto input = modelsContext()->input(meta.tournamentId,meta.currentPlayerId,index);
            updateScoreDetails(input);
        }
    },future);
}
void DartsController::addInputToModelsContext(AbstractDartsInput *input)
{
    auto index = indexController()->index();
    setInputStats()->set(input,playerStats(),calcMidVal(),index,metaInfo()->get().initialRemainingScore);
    auto meta = createMeta()->create(metaInfo(),index,scoreModels());
    indexController()->next(playerController()->count());
    auto addInput = modelsContext()->addInput(meta.tournamentId,input);
    RunLater::run([=]{
        auto updateIndex = modelsContext()->updateTournamentIndex(metaInfo()->get().tournamentId,indexController()->index());
        RunLater::run([=]{
            auto inputVal = modelsContext()->input(metaInfo()->get().tournamentId,meta.currentPlayerId,indexController()->index());
            updateScoreDetails(inputVal);
        },updateIndex);
    },addInput);
}
int DartsController::initialize(const QUuid &tournamentId)
{
    auto tournament = modelsContext()->tournament(tournamentId);
    DCInit::initTournamentMeta(tournament,metaInfo());
    auto players = modelsContext()->assignedPlayers(tournamentId);
    DCInit::initPlayerDetails(players,metaInfo()->get(),scoreModels(),scoresBuilder(),playerStats(),playerController());
    auto inputs = modelsContext()->tournamentInputs(tournamentId);
    DCInit::initScores(inputs,updatePlayerScores(),updatePlayerStats(),scoreModels(),playerStats());
    return statusCodes()->initialized();
}
QString DartsController::tournamentId() const
{
    return metaInfo()->get().tournamentId.toString(QUuid::WithBraces);
}
QByteArray DartsController::getTurnValuesJson()
{
    if(metaInfo()->get().status == statusCodes()->winnerFound())
        return createWinnerJson();
    return createTurnValuesJson();
}
QByteArray DartsController::createWinnerJson()
{
    auto meta = createMeta()->create(metaInfo(),indexController()->index(),scoreModels());
    return createJson()->create(meta);
}
