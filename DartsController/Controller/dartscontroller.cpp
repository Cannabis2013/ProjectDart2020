#include "dartscontroller.h"
int DartsController::handleInput(const QByteArray& json)
{
    if(metaContext()->get().status == statusCodes()->winnerFound()) return -1;
    auto input = createInput()->create(json);
    auto scoreCand = scoreCalculator()->calculate(idxCtrl()->index(),input->score(),scoresCtx());
    evaluateInput()->evaluate(input,scoreCand,metaContext(),this,statusCodes(),playersCtx());
    return 0;
}
void DartsController::addInputToModelsContext(AbstractDartsInput *input)
{
    setInputStats()->set(input);
    auto newIndex = idxCtrl()->next();
    mdsCtx()->addInput(metaContext()->get().tournamentId,input,[=]{
        auto updateIndex = mdsCtx()->updateTournamentIndex(metaContext()->get().tournamentId,newIndex);
        RunLater::run<bool>(updateIndex,[=](const bool &){updateScoreDetails(input);});
    });
}
void DartsController::updateScoreDetails(AbstractDartsInput *input)
{
    updatePlayerStats()->update(input,statsCtx());
    playersCtx()->updateStatus(input->playerId(),input->inGame());
    auto scoreModel = &scoresCtx()->score(input->playerId());
    scoreModel->remainingScore = input->remainingScore();
    emit updatePlayerScore(createJson()->create(input));
}
QByteArray DartsController::getPlayerScores() const
{
    return createJson()->create(scoresCtx()->scores(),statsCtx()->stats());
}
void DartsController::reset()
{
    DCResetContexts::reset(idxCtrl(),scoresCtx(),statsCtx(),metaContext(),playersCtx(),statusCodes());
    RunLater::run<bool>(mdsCtx()->resetTournament(metaContext()->get().tournamentId),[=](const bool &result){if(result)emit resetSucces();});
}
int DartsController::status() const
{
    return metaContext()->get().status;
}
void DartsController::undoTurn()
{
    auto inputIndex = idxCtrl()->undo();
    auto meta = createMeta()->create();
    mdsCtx()->hideInput(meta.tournamentId,meta.currentPlayerId,inputIndex,[=]{
        auto reqIndex = reqIndexBuilder()->prevIndex();
        auto input = mdsCtx()->input(meta.tournamentId,meta.currentPlayerId,reqIndex);
        if(input == nullptr) input = createInput()->createDefault();
        updateScoreDetails(input);
    });
}
void DartsController::redoTurn()
{
    auto meta = createMeta()->create();
    auto index = idxCtrl()->index();
    idxCtrl()->redo();
    mdsCtx()->revealInput(meta.tournamentId,meta.currentPlayerId,index,[=]{
        auto input = mdsCtx()->input(meta.tournamentId,meta.currentPlayerId,index);
        updateScoreDetails(input);
    });
}
int DartsController::initialize(const QUuid &tournamentId)
{
    DCInit::initTournamentMeta(mdsCtx()->tournament(tournamentId),metaContext(),idxCtrl());
    DCInit::initPlayerDetails(mdsCtx()->assignedPlayers(tournamentId),metaContext()->get(),scoresCtx(),scoresBuilder(),statsCtx(),playersCtx());
    DCInit::initScores(mdsCtx()->tournamentInputs(tournamentId),updatePlayerScores(),updatePlayerStats(),scoresCtx(),statsCtx());
    return statusCodes()->initialized();
}
QString DartsController::tournamentId() const
{
    return metaContext()->get().tournamentId.toString(QUuid::WithBraces);
}
QByteArray DartsController::getTurnValues() const
{
    return createJson()->create(turnValuesBuilder()->turnValues());
}
QByteArray DartsController::getWinnerJson() const
{
    return createJson()->create(createMeta()->winnerMeta());
}
