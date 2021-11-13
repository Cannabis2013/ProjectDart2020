#include "dartscontroller.h"
void DartsController::createIndexJson()
{
    auto future = modelsContext()->updateTournamentIndex(metaInfo()->get().tournamentId,indexController()->index());
    Runnable::runLater([=]{
        if(future.result())
            createJsonResponse();
    },future);
}
void DartsController::handleUserInput(const QByteArray& json)
{
    auto input = createInput()->create(json,playerController(),scoreCalculator(),indexController()->index(),scoreModels());
    auto scoreCand = scoreCalculator()->calculate(indexController()->index(),input->score(),scoreModels());
    evaluateInput()->evaluate(input,scoreCand,metaInfo(),this,statusCodes(),playerController());
}
void DartsController::sendTournamentId()
{
    emit sendCurrentTournamentId(metaInfo()->get().tournamentId);
}
QByteArray DartsController::createScores()
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
    Runnable::runLater([=]{
        if(future.result())
            emit resetSucces();
    },future);
}
void DartsController::createTurnValuesJson()
{
    auto values = turnValuesBuilder()->turnValues(indexController()->index(),scoreModels(),dartsFinishBuilder());
    emit sendTurnValues(createJson()->create(values));
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
    Runnable::runLater([=]{
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
    Runnable::runLater([=]{
        if(future.result())
        {
            auto input = modelsContext()->input(meta.tournamentId,meta.currentPlayerId,index);
            updateScoreDetails(input);
        }
    },future);
}
void DartsController::persistInput(AbstractDartsInput *input)
{
    auto index = indexController()->index();
    setInputStats()->set(input,playerStats(),calcMidVal(),index,metaInfo()->get().initialRemainingScore);
    auto meta = createMeta()->create(metaInfo(),index,scoreModels());
    indexController()->next(playerController()->count());
    auto json = createJson()->create(input,index,meta);
    auto future = modelsContext()->addInput(json);
    Runnable::runLater([=]{
        auto meta = metaInfo()->get();
        auto inputVal = modelsContext()->input(meta.tournamentId,meta.currentPlayerId,indexController()->index());
        updateScoreDetails(inputVal);}
    ,future);
}
void DartsController::createJsonResponse()
{
    if(metaInfo()->get().status == statusCodes()->winnerFound())
        createWinnerJson();
    else
        createTurnValuesJson();
}
int DartsController::initialize(const QUuid &tournamentId, const int &remainingScore)
{
    auto players = modelsContext()->assignedPlayers(tournamentId);
    DCInit::initPlayerDetails(players,metaInfo()->get(),scoreModels(),scoresBuilder(),playerStats(),playerController());
    return statusCodes()->initialized();
}

QString DartsController::tournamentId() const
{
    return metaInfo()->get().tournamentId.toString(QUuid::WithBraces);
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
