#include "dscinjectplaservives.h"

#include <DartsController/Players/dcplayersservices.h>

#include <LocalDartsController/Players/dcconvertplayers.h>
#include <LocalDartsController/Players/dcplayerbuilder.h>
#include <LocalDartsController/Players/dcplayertojson.h>
#include <LocalDartsController/Players/dscplayerscontext.h>
#include <DartsController/ServicesProvider/dcservices.h>

void DSCInjectPlaServives::inject(DCServices *dc) const
{
    auto playerServices = new DCPlayersServices;
    playerServices->setPlayerConverter(new DCPlayerBuilder);
    playerServices->setConvertPlayers(new DCConvertPlayers);
    playerServices->setPlayerManager(new DSCPlayersContext);
    playerServices->setPlayerToJson(new DCPlayerToJson);
    dc->setPlayerServices(playerServices);
}
