#include "dscinjectplaservives.h"
#include "DCScoresSLAs/dcplayersservices.h"
#include "DCScoresServices/dscplayerscontext.h"
#include "DCScoresServices/dcconvertplayers.h"
#include "DCScoresServices/dcplayerbuilder.h"
#include "ServicesProvider/dcservices.h"

void DSCInjectPlaServives::inject(DCServices *dc) const
{
    auto playerServices = new DCPlayersServices;
    playerServices->setPlayerConverter(new DCPlayerBuilder);
    playerServices->setConvertPlayers(new DCConvertPlayers);
    playerServices->setPlayerManager(new DSCPlayersContext);
    dc->setPlayerServices(playerServices);
}
