#include "dartscontroller.h"
QByteArray DartsController::addInput(const QByteArray& json)
{
    auto player = playersContext()->player(idxCtrl()->index());
    auto ipt = createInput()->create(json,idxCtrl()->index(),player);
    auto scoreCand = scoreCalc()->calc(ipt.score); // Calc score
    evalIpt()->eval(ipt,scoreCand,metaCtx()->get(),player,metaCtx()->WinnerDeclared); // Evaluate input
    updateInputStats()->set(ipt,idxCtrl()->index(),metaCtx()->initRemScore());
    auto idx = idxCtrl()->next(); // Increment index controller
    addToModelsCtx()->add(ipt,idx,mdsCtx()); // Persist input to models context
    updatePlayerDetails()->update(ipt);
    if(metaCtx()->status() == metaCtx()->WinnerDeclared)
        mdsCtx()->setTournamentWinner(metaCtx()->tournamentId(),metaCtx()->winnerName());
    return createJson()->create(ipt); // Return input model as json to calling context
}
bool DartsController::reset()
{
    idxCtrl()->init();
    playersContext()->reset(metaCtx()->get().initRemScore);
    statsContext()->reset();
    metaCtx()->set(IDCMetaContext::Initialized);
    return mdsCtx()->resetTournament(metaCtx()->tournamentId());
}
QByteArray DartsController::undoTurn()
{
    auto inputIdx = idxCtrl()->undo();
    auto meta = createMeta()->create();
    mdsCtx()->hideInput(meta.tournamentId,meta.playerName,idxConverter()->convert(inputIdx));
    auto reqIndex = reqIndexBuilder()->prevIdx();
    auto cvtReqIdx = idxConverter()->convert(reqIndex);
    auto mdIpt = mdsCtx()->input(metaCtx()->tournamentId(),meta.playerName,cvtReqIdx);
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
    DCInit::initTournamentMeta(mdsCtx()->tournament(tournamentId),metaCtx(),idxCtrl(),idxConverter());
    DCInit::initPlayerDetails(mdsCtx()->players(tournamentId),metaCtx()->get(),playersContext(),statsContext());
    DCInit::initScores(iptConverter()->convert(mdsCtx()->inputs(tournamentId)),statsContext(),playersContext());
    DCInit::initStatus(metaCtx());
    return metaCtx()->Initialized;
}
