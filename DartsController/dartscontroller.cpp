#include "dartscontroller.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"
QString DartsController::tournamentId() const {return metaService()->tournamentId().toString(QUuid::WithBraces);}
QByteArray DartsController::getPlayerScores() const {return createJson()->create(plaCtx()->players(),statisticsService()->stats());}
int DartsController::status() const {return metaService()->status();}
int DartsController::initialize(const QUuid &tournamentId)
{
    loader()->init(tournamentId,mdsCtx());
    return metaService()->Initialized;
}
QByteArray DartsController::addInput(const QByteArray& json)
{
    auto ipt = assembleInput()->assemble(json);
    evalIpt()->eval(ipt);
    updateStatistics()->update(ipt);
    addToModelsService()->add(ipt,mdsCtx());
    return createJson()->create(ipt,metaService()->meta());
}
bool DartsController::reset()
{
    resetServices()->reset();
    return mdsCtx()->resetTournament(metaService()->tournamentId());
}
QByteArray DartsController::undoTurn()
{
    hideInput();
    auto ipt = getInputFromMdsService()->getPreviousInput();
    updateServices(ipt);
    return createJson()->create(ipt,metaService()->meta());
}
QByteArray DartsController::redoTurn()
{
    revealInput();
    auto ipt = getInputFromMdsService()->getCurrentInput();
    updateServices(ipt);
    indexService()->redo();
    return createJson()->create(ipt,metaService()->meta());
}
QByteArray DartsController::getTurnValues() const {
    auto values = createCurrentTurnValues();
    return createJson()->create(values,metaService()->meta());
}
QByteArray DartsController::getWinnerJson() const {return createJson()->create(createMeta()->winnerMeta(metaService(),indexService(),plaCtx()));}
