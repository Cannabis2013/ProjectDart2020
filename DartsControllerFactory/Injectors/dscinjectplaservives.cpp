#include "dscinjectplaservives.h"
#include "Players/dcplayersservices.h"
#include "Players/dscplayerscontext.h"
#include "Players/dcconvertplayers.h"
#include "Players/dcplayerbuilder.h"
#include "ServicesProvider/dcservices.h"
#include "Players/dcplayertojson.h"
void DSCInjectPlaServives::inject(DCServices *dc) const
{
    auto playerServices = new DCPlayersServices;
    playerServices->setPlayerConverter(new DCPlayerBuilder);
    playerServices->setConvertPlayers(new DCConvertPlayers);
    playerServices->setPlayerManager(new DSCPlayersContext);
    playerServices->setPlayerToJson(new DCPlayerToJson);
    dc->setPlayerServices(playerServices);
}
