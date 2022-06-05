#include "dpcinjectplaservices.h"
#include <DartsController/Players/dcplayersservices.h>
#include <LocalDartsController/Players/dcconvertplayers.h>
#include <LocalDartsController/Players/dcplayerbuilder.h>
#include <LocalDartsController/Players/dcplayertojson.h>
#include <LocalDartsController/Players/dpcplayerscontext.h>
#include <DartsController/ServicesProvider/dcservices.h>

void DPCInjectPlaServices::inject(DCServices *dc) const
{
    auto playerServices = new DCPlayersServices;
    playerServices->setPlayerConverter(new DCPlayerBuilder);
    playerServices->setConvertPlayers(new DCConvertPlayers);
    playerServices->setPlayerManager(new DPCPlayersContext);
    playerServices->setPlayerToJson(new DCPlayerToJson);
    dc->setPlayerServices(playerServices);
}
