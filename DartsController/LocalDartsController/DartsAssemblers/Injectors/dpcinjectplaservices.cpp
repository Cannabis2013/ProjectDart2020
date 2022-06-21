#include "dpcinjectplaservices.h"
#include <DartsController/Contracts/Players/dcplayersservices.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/LocalDartsController/Players/dcconvertplayers.h>
#include <DartsController/LocalDartsController/Players/dcplayerbuilder.h>
#include <DartsController/LocalDartsController/Players/dcplayertojson.h>
#include <DartsController/LocalDartsController/Players/dpcplayerscontext.h>

void DPCInjectPlaServices::inject(DCServices *dc) const
{
    auto playerServices = new DCPlayersServices;
    playerServices->setPlayerConverter(new DCPlayerBuilder);
    playerServices->setConvertPlayers(new DCConvertPlayers);
    playerServices->setPlayerManager(new DPCPlayersContext);
    playerServices->setPlayerToJson(new DCPlayerToJson);
    dc->setPlayerServices(playerServices);
}
