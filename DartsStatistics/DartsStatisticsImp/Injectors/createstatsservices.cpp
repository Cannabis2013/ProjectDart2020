#include "createstatsservices.h"

#include <DartsStatistics/Contracts/StatsServices/StatsServices.h>
#include <DartsStatistics/DartsStatisticsImp/Statistics/calculatemiddlevalue.h>
#include <DartsStatistics/DartsStatisticsImp/Statistics/updatescorerange.h>

StatsServices *CreateStatsServices::create() const
{
    auto statsProvider = new StatsServices;
    statsProvider->setCalcAverage(new CalculateMiddleValue);
    statsProvider->setUpdateScoreRange(new UpdateScoreRange);
    return statsProvider;
}
