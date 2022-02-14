#include "dpcinjectplaservices.h"
#include "Players/dcplayersservices.h"
#include "Players/dcconvertplayers.h"
#include "Players/dcplayerbuilder.h"
#include "Players/dpcplayerscontext.h"
#include "ServicesProvider/dcservices.h"
#include "Players/dcplayertojson.h"

void DPCInjectPlaServices::inject(DCServices *dc) const
{
    auto playerServices = new DCPlayersServices;
    playerServices->setPlayerConverter(new DCPlayerBuilder);
    playerServices->setConvertPlayers(new DCConvertPlayers);
    playerServices->setPlayerManager(new DPCPlayersContext);
    playerServices->setPlayerToJson(new DCPlayerToJson);
    dc->setPlayerServices(playerServices);
}
