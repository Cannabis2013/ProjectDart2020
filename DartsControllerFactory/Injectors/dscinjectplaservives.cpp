#include "dscinjectplaservives.h"
#include "DCScoresSLAs/dcplayersslas.h"
#include "DCScoresServices/dscplayerscontext.h"
#include "DSCServices/dsccreatescore.h"
#include "DCScoresServices/dcconvertplayers.h"
#include "DCScoresServices/dcplayerbuilder.h"

void DSCInjectPlaServives::inject(DCPlayersSLAs *dc) const
{
    dc->setPlayerConverter(new DCPlayerBuilder);
    dc->setConvertPlayers(new DCConvertPlayers);
    dc->setGetScoreFromInput(new DSCCreateScore);
    dc->setPlayersContext(new DSCPlayersContext);
}
