#include "dscinjectplaservives.h"
#include "DCScoresServices/dcconvertplayers.h"
#include "DCScoresServices/dcplayerbuilder.h"
#include "DCScoresServices/dscplayerscontext.h"
#include "DSCServices/dsccreatescore.h"
#include "DCScoresSLAs/dcplayersslas.h"
#include "DCScoresServices/dcupdplastats.h"

void DSCInjectPlaServives::inject(DCPlayersSLAs *dc) const
{
    dc->setPlayerConverter(new DCPlayerBuilder);
    dc->setGetScoreFromInput(new DSCCreateScore);
    dc->setConvertPlayers(new DCConvertPlayers);
    dc->setPlayersContext(new DSCPlayersContext);
    dc->setUpdateScores(new DCUpdatePlayerStats);
}
