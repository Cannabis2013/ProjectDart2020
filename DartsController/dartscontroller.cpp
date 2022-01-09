#include "dartscontroller.h"
#include "TournamentModels/tnmvalues.h"
#include "StaticInitHelperClass/dcinit.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"
#include "DCIndexSLAs/idcidxctrl.h"
#include "DCIndexSLAs/idcidxbuilder.h"
QString DartsController::tournamentId() const {return metaCtx()->tournamentId().toString(QUuid::WithBraces);}
QByteArray DartsController::getPlayerScores() const {return createJson()->create(playersContext()->players(),statsContext()->stats());}
int DartsController::status() const {return metaCtx()->status();}
int DartsController::initialize(const QUuid &tournamentId){
    auto meta = createMeta()->create(mdsCtx()->tournament(tournamentId));
    DCInit::initTournamentMeta(meta,metaCtx(),idxCtrl());
    DCInit::initPlayerDetails(mdsCtx()->players(tournamentId),metaCtx()->get(),playersContext(),statsContext());
    DCInit::initScores(iptConverter()->convert(mdsCtx()->inputs(tournamentId)),statsContext(),playersContext());
    DCInit::initStatus(metaCtx());
    return metaCtx()->Initialized;
}
QByteArray DartsController::addInput(const QByteArray& json)
{
    auto index = idxCtrl()->index();
    auto player = playersContext()->player(index.setIndex);
    auto ipt = createInput()->create(json,index,player);
    auto scoreCand = scoreCalc()->calc(ipt.score,player.remScore); // Calc score
    evalIpt()->eval(ipt,scoreCand,metaCtx()->get(),player,metaCtx()->WinnerDeclared); // Evaluate input
    updateInputStats()->set(ipt,index,metaCtx()->initRemScore());
    auto idx = idxCtrl()->next(); // Increment index
    addToModelsCtx()->add(ipt,idx,metaCtx()->get(),mdsCtx()); // Persist input to models context
    updatePlayerDetails()->update(ipt);
    if(metaCtx()->status() == metaCtx()->WinnerDeclared)
        mdsCtx()->setTournamentWinner(metaCtx()->tournamentId(),metaCtx()->winnerName());
    return createJson()->create(ipt,DCMeta()); // Return input model as json to calling context
}
bool DartsController::reset()
{
    idxCtrl()->init(metaCtx()->get());
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
    auto cvtReqIdx = idxConverter()->convert(idxCtrl()->prevIndex());
    auto mdIpt = mdsCtx()->input(metaCtx()->tournamentId(),meta.playerName,cvtReqIdx);
    auto player = playersContext()->player(meta.playerName);
    auto ipt = iptConverter()->convert(mdIpt,meta.initRemScore,player);
    updatePlayerDetails()->update(ipt);
    return createJson()->create(ipt,DCMeta());
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
    return createJson()->create(ipt,DCMeta());
}
QByteArray DartsController::getTurnValues() const {
    auto idx = idxCtrl()->index();
    auto player = playersContext()->player(idx.setIndex);
    auto finish = finishBuilder()->suggestTargetRow(player.remScore,idx.attemptIndex);
    auto values = turnValuesBuilder()->create(idx,player,finish);
    return createJson()->create(values,DCMeta());
}
QByteArray DartsController::getWinnerJson() const {
    return createJson()->create(createMeta()->winnerMeta());
}
