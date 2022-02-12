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
    auto index = _services->indexController()->prevIndex();
    return getInput(index);
}

DCInput DCExternalInputService::getCurrentInput()
{
    auto index = _services->indexController()->index();
    return getInput(index);
}

DCInput DCExternalInputService::getInput(const DCIndex &index)
{
    auto meta = _services->metaService()->meta();
    auto tournamentId = _services->metaService()->tournamentId();
    auto player = _services->playerManager()->player(index.playerIndex);
    auto idxBa = _services->indexToByteArray()->convert(index);
    auto iptBa = _services->modelsContext()->input(tournamentId,player.name,idxBa);
    auto ipt = _services->iptBuilder()->create(iptBa,meta.initRemScore);
    _services->AddInputDetails()->add(ipt,player,meta);
    return ipt;
}


void DCExternalInputService::hideInput()
{
    auto idx = _services->indexController()->index();
    auto metaService = _services->metaService();
    auto indexService = _services->indexController();
    auto playerService = _services->playerManager();
    auto meta = _services->createMeta()->create(metaService,indexService,playerService);
    auto idxBa = _services->indexToByteArray()->convert(idx);
    auto mdsService = _services->modelsContext();
    mdsService->hideInput(meta.tournamentId,meta.playerName,idxBa);
}

void DCExternalInputService::displayInput()
{
    auto idx = _services->indexController()->index();
    auto metaService = _services->metaService();
    auto indexService = _services->indexController();
    auto playerService = _services->playerManager();
    auto meta = _services->createMeta()->create(metaService,indexService,playerService);
    auto idxBa = _services->indexToByteArray()->convert(idx);
    auto mdsService = _services->modelsContext();
    mdsService->revealInput(meta.tournamentId,meta.playerName,idxBa);
}
