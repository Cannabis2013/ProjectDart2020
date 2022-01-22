#include "dartscontroller.h"
#include "StaticInitHelperClass/dcinitialize.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"
#include "DCIndexSLAs/idcindexcontroller.h"
#include "DCIndexSLAs/idcindexconverter.h"
#include "PlayerStatsSLAs/idcsetiptstats.h"
#include "PlayerStatsSLAs/idcstatistics.h"
#include "InitRoutines/dcloadmodels.h"

QString DartsController::tournamentId() const {return metaCtx()->tournamentId().toString(QUuid::WithBraces);}
QByteArray DartsController::getPlayerScores() const {return createJson()->create(playersContext()->players(),statistics()->stats());}
int DartsController::status() const {return metaCtx()->status();}
int DartsController::initialize(const QUuid &tournamentId)
{
    DCLoadModels loadModels(createMeta(),playerConverter(),convertPlayers(),inputBuilder(),convertInputs());
    loadModels.load(tournamentId,mdsCtx());
    DCInitialize initializer(playersContext(),statistics(),metaCtx(),idxCtrl());
    initializer.init(loadModels.players(),loadModels.meta(),loadModels.inputs());
    return metaCtx()->Initialized;
}
QByteArray DartsController::addInput(const QByteArray& json)
{
    auto ipt = inputBuilder()->create(json);
    auto index = idxCtrl()->index();
    auto player = playersContext()->player(index.playerIndex);
    AddInputDetails()->add(ipt,index,player,metaCtx()->meta());
    auto scoreCand = scoreCalc()->calc(ipt.score,player.remScore);
    evalIpt()->eval(ipt,scoreCand,metaCtx()->meta(),player,metaCtx()->WinnerDeclared);
    updateInputStats()->set(ipt,index,metaCtx()->initRemScore(),statistics());
    auto idx = idxCtrl()->next();
    addToModelsCtx()->add(ipt,idx,metaCtx()->meta(),mdsCtx(),inputBuilder(),idxConverter());
    updatePlayerDetails()->update(ipt,statistics(),playersContext());
    if(metaCtx()->status() == metaCtx()->WinnerDeclared)
        mdsCtx()->setTournamentWinner(metaCtx()->tournamentId(),metaCtx()->winnerName());
    return createJson()->create(ipt,metaCtx()->meta());
}
bool DartsController::reset()
{
    idxCtrl()->init(metaCtx()->meta());
    playersContext()->reset(metaCtx()->meta().initRemScore);
    statistics()->reset();
    metaCtx()->setMeta(IDCMetaContext::Initialized);
    return mdsCtx()->resetTournament(metaCtx()->tournamentId());
}
QByteArray DartsController::undoTurn()
{
    auto inputIdx = idxCtrl()->undo();
    auto meta = createMeta()->create(metaCtx(),idxCtrl(),playersContext());
    mdsCtx()->hideInput(meta.tournamentId,meta.playerName,idxConverter()->convert(inputIdx));
    auto cvtReqIdx = idxConverter()->convert(idxCtrl()->prevIndex());
    auto iptBa = mdsCtx()->input(metaCtx()->tournamentId(),meta.playerName,cvtReqIdx);
    auto player = playersContext()->player(meta.playerName);
    auto ipt = inputBuilder()->create(iptBa,metaCtx()->initRemScore());
    AddInputDetails()->add(ipt,ipt.remScore,player,meta);
    updatePlayerDetails()->update(ipt,statistics(),playersContext());
    return createJson()->create(ipt,metaCtx()->meta());
}
QByteArray DartsController::redoTurn()
{
    auto meta = createMeta()->create(metaCtx(),idxCtrl(),playersContext());
    auto idx = idxConverter()->convert(idxCtrl()->index());
    idxCtrl()->redo();
    mdsCtx()->revealInput(meta.tournamentId,meta.playerName,idx);
    auto iptBa = mdsCtx()->input(meta.tournamentId,meta.playerName,idx);
    auto player = playersContext()->player(meta.playerName);
    auto ipt = inputBuilder()->create(iptBa);
    AddInputDetails()->add(ipt,ipt.remScore,player,meta);
    updatePlayerDetails()->update(ipt,statistics(),playersContext());
    return createJson()->create(ipt,meta);
}
QByteArray DartsController::getTurnValues() const {
    auto meta = createMeta()->create(metaCtx(),idxCtrl(),playersContext());
    auto idx = idxCtrl()->index();
    auto player = playersContext()->player(idx.playerIndex);
    auto finish = finishBuilder()->suggestTargetRow(player.remScore,idx.attemptIndex);
    auto values = turnValuesBuilder()->create(idx,player,finish);
    return createJson()->create(values,meta);
}
QByteArray DartsController::getWinnerJson() const {return createJson()->create(createMeta()->winnerMeta(metaCtx(),idxCtrl(),playersContext()));}
