#include "updatescorerange.h"
#include <DartsStatistics/Contracts/Inputs/Models/snapshot.h>
#include <DartsStatistics/Contracts/Players/Models/playerstats.h>

void UpdateScoreRange::update(SnapShot &snapShot, PlayerStats *stats) const
{
        auto score = snapShot.score;
        auto currentMin = stats->min;
        auto currentMax = stats->max;
        if(score < currentMin)
                stats->min = score;
        else if(score > currentMax)
                stats->max = score;
}
