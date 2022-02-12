#include "dpcinjectplaservices.h"
#include "DCScoresSLAs/dcplayersslas.h"
#include "DCScoresServices/dcconvertplayers.h"
#include "DCScoresServices/dcplayerbuilder.h"
#include "DCScoresServices/dpcplayerscontext.h"

void DPCInjectPlaServices::inject(DCPlayersSLAs *dc) const
{
    dc->setPlayerConverter(new DCPlayerBuilder);
    dc->setConvertPlayers(new DCConvertPlayers);
    dc->setPlayerManager(new DPCPlayersContext);
}
