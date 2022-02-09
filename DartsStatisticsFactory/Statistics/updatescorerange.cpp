#include "updatescorerange.h"
#include "Inputs/Models/snapshot.h"
#include "Players/Models/imirrorsdb.h"

void UpdateScoreRange::update(SnapShot &snapShot, CurrentStat *stats) const
{
    auto score = snapShot.score;
    auto currentMin = stats->min;
    auto currentMax = stats->max;
    if(score < currentMin)
        stats->min = score;
    else if(score > currentMax)
        stats->max = score;
}
