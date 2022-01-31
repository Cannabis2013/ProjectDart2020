#include "dcexternalinputservice.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcinput.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcmeta.h"

DCExternalInputService::DCExternalInputService(DCServices *services): _services(services){}

DCInput DCExternalInputService::getPreviousInput()
{
    auto index = _services->indexService()->prevIndex();
    return getInput(index);
}

DCInput DCExternalInputService::getCurrentInput()
{
    auto index = _services->indexService()->index();
    return getInput(index);
}

DCInput DCExternalInputService::getInput(const DCIndex &index)
{
    auto meta = _services->metaService()->meta();
    auto tournamentId = _services->metaService()->tournamentId();
    auto player = _services->playerService()->player(index.playerIndex);
    auto idxBa = _services->idxConverter()->convert(index);
    auto iptBa = _services->mdsCtx()->input(tournamentId,player.name,idxBa);
    auto ipt = _services->iptBuilder()->create(iptBa,meta.initRemScore);
    _services->AddInputDetails()->add(ipt,player,meta);
    return ipt;
}


void DCExternalInputService::hideInput()
{
    auto idx = _services->indexService()->index();
    auto metaService = _services->metaService();
    auto indexService = _services->indexService();
    auto playerService = _services->playerService();
    auto meta = _services->createMeta()->create(metaService,indexService,playerService);
    auto idxBa = _services->idxConverter()->convert(idx);
    auto mdsService = _services->mdsCtx();
    mdsService->hideInput(meta.tournamentId,meta.playerName,idxBa);
}

void DCExternalInputService::displayInput()
{
    auto idx = _services->indexService()->index();
    auto metaService = _services->metaService();
    auto indexService = _services->indexService();
    auto playerService = _services->playerService();
    auto meta = _services->createMeta()->create(metaService,indexService,playerService);
    auto idxBa = _services->idxConverter()->convert(idx);
    auto mdsService = _services->mdsCtx();
    mdsService->revealInput(meta.tournamentId,meta.playerName,idxBa);
}
