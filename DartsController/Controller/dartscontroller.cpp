#include "dartscontroller.h"
QByteArray DartsController::addInput(const QByteArray& json)
{
    auto player = playersContext()->player(idxCtrl()->index());
    auto ipt = createInput()->create(json,idxCtrl()->index(),player);
    auto scoreCand = scoreCalc()->calc(ipt.score);
    evaluateIpt()->evaluate(ipt,scoreCand);
    updateInputStats()->set(ipt,idxCtrl()->index(),metaContext()->initRemScore());
    addToModelsCtx()->add(ipt,mdsCtx());
    updatePlayerDetails()->update(ipt);
    if(metaContext()->status() == metaContext()->WinnerDeclared)
        mdsCtx()->setTournamentWinner(metaContext()->tournamentId(),metaContext()->winnerName());
    return createJson()->create(ipt);
}
bool DartsController::reset()
{
    DCResetContexts::reset(idxCtrl(),playersContext(),statsContext(),metaContext());
    return mdsCtx()->resetTournament(metaContext()->tournamentId());
}
QByteArray DartsController::undoTurn()
{
    auto inputIdx = idxCtrl()->undo();
    auto meta = createMeta()->create();
    mdsCtx()->hideInput(meta.tournamentId,meta.playerName,idxConverter()->convert(inputIdx));
    auto reqIndex = reqIndexBuilder()->prevIdx();
    auto cvtIdx = idxConverter()->convert(reqIndex);
    auto mdIpt = mdsCtx()->input(metaContext()->tournamentId(),meta.playerName,cvtIdx);
    auto player = playersContext()->player(meta.playerName);
    auto ipt = iptConverter()->convert(mdIpt,meta.initRemScore,player);
    updatePlayerDetails()->update(ipt);
    return createJson()->create(ipt);
}
QByteArray DartsController::redoTurn()
{
    auto meta = createMeta()->create();
    auto idx = idxConverter()->convert(idxCtrl()->index());
    idxCtrl()->redo();
    mdsCtx()->revealInput(meta.tournamentId,meta.playerName,idx);
    auto mdlInput = mdsCtx()->input(meta.tournamentId,meta.playerName,idx);
    auto player = playersContext()->player(meta.playerName);
    auto ipt = iptConverter()->convert(mdlInput,meta.initRemScore,player);
    updatePlayerDetails()->update(ipt);
    return createJson()->create(ipt);
}
int DartsController::initialize(const QUuid &tournamentId)
{
    DCInit::initTournamentMeta(mdsCtx()->tournament(tournamentId),metaContext(),idxCtrl(),idxConverter());
    DCInit::initPlayerDetails(mdsCtx()->players(tournamentId),metaContext()->get(),playersContext(),statsContext());
    DCInit::initScores(iptConverter()->convert(mdsCtx()->inputs(tournamentId)),statsContext(),playersContext());
    DCInit::initStatus(metaContext());
    return metaContext()->Initialized;
}
