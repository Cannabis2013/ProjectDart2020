#include "dpcinjectplaservices.h"
#include "DCScoresSLAs/dcplayersservices.h"
#include "DCScoresServices/dcconvertplayers.h"
#include "DCScoresServices/dcplayerbuilder.h"
#include "DCScoresServices/dpcplayerscontext.h"
#include "ServicesProvider/dcservices.h"

void DPCInjectPlaServices::inject(DCServices *dc) const
{
    auto playerServices = new DCPlayersServices;
    playerServices->setPlayerConverter(new DCPlayerBuilder);
    playerServices->setConvertPlayers(new DCConvertPlayers);
    playerServices->setPlayerManager(new DPCPlayersContext);
    dc->setPlayerServices(playerServices);
}
