#include "dcassembleinput.h"
#include <qbytearray.h>
#include "Models/dcinput.h"
#include "Models/dcindex.h"
#include "Models/dcinput.h"
#include "Models/dcplayer.h"
#include "Models/dcmeta.h"
#include "ServicesProvider/dcservices.h"

DCAssembleInput::DCAssembleInput(DCServices *services)
{
    _services = services;
}

DCInput DCAssembleInput::convert(const QByteArray &byteArray) const
{
    auto meta = _services->metaService()->meta();
    auto index = _services->indexController()->index();
    auto ipt = _services->iptBuilder()->create(byteArray);
    auto player = _services->playerManager()->player(index.playerIndex);
    addDetails(ipt,index,meta,player);
    return ipt;
}

void DCAssembleInput::addDetails(DCInput &input, const DCIndex &idx,const DCMeta &meta, const DCPlayer &player) const
{
    input.playerName = player.name;
    input.playerId = player.id;
    input.remScore = player.remScore;
    input.inGame = player.in;
    input.roundIndex = idx.roundIndex;
    input.playerIndex = idx.playerIndex;
    input.attemptIndex = idx.attemptIndex;
    input.tournamentId = meta.tournamentId;
}
