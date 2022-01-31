#include "dcupdatemodelscontext.h"
#include "Models/dcinput.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcindex.h"
#include "Models/dcmeta.h"
#include <qjsondocument.h>
#include "ServicesProvider/dcservices.h"
DCUpdateModelsContext::DCUpdateModelsContext(DCServices *services):_services(services){}

bool DCUpdateModelsContext::add(DCInput &ipt, AbsDartsCtx *mdsCtx)
{
    auto nextIndex = _services->indexService()->next();
    auto meta = _services->metaService()->meta();
    auto cvtdIdx = _services->idxConverter()->convert(nextIndex);
    auto iptJson = _services->iptBuilder()->create(ipt);
    auto iptBa = QJsonDocument(iptJson).toJson();
    auto inputAdded = mdsCtx->addInput(meta.tournamentId,iptBa);
    auto indexUpdated = mdsCtx->updateTournamentIndex(meta.tournamentId,cvtdIdx);
    if(meta.status == _services->metaService()->WinnerDeclared)
        mdsCtx->setTournamentWinner(meta.tournamentId,meta.winnerName);
    _services->statisticsService()->update(ipt);
    _services->playerService()->updateScore(ipt);
    return inputAdded && indexUpdated;
}

