#include "createstatsservices.h"

#include <DartsStatistics/StatsServices/StatsServices.h>
#include <DartsStatisticsFactory/Statistics/calculatemiddlevalue.h>
#include <DartsStatisticsFactory/Statistics/updatescorerange.h>

StatsServices *CreateStatsServices::create() const
{
    auto statsProvider = new StatsServices;
    statsProvider->setCalcAverage(new CalculateMiddleValue);
    statsProvider->setUpdateScoreRange(new UpdateScoreRange);
    return statsProvider;
}
