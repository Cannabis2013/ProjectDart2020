#include "dcgetinput.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcinput.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcmeta.h"

DCGetInput::DCGetInput(DCServices *services): _services(services){}

DCInput DCGetInput::getPreviousInput()
{
    auto index = _services->indexService()->prevIndex();
    return getInput(index);
}

DCInput DCGetInput::getCurrentInput()
{
    auto index = _services->indexService()->index();
    return getInput(index);
}

DCInput DCGetInput::getInput(const DCIndex &index)
{
    auto meta = _services->metaService()->meta();
    auto tournamentId = _services->metaService()->tournamentId();
    auto player = _services->plaCtx()->player(index.playerIndex);
    auto idxBa = _services->idxConverter()->convert(index);
    auto iptBa = _services->mdsCtx()->input(tournamentId,player.name,idxBa);
    auto ipt = _services->iptBuilder()->create(iptBa,meta.initRemScore);
    _services->AddInputDetails()->add(ipt,player,meta);
    return ipt;
}
