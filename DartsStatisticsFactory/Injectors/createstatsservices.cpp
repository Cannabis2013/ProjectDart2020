#include "createstatsservices.h"
#include "SLAs/servicescontext.h"
#include "Statistics/calculatemiddlevalue.h"
#include "Statistics/updatescorerange.h"

StatsServices *CreateStatsServices::create() const
{
    auto statsProvider = new StatsServices;
    statsProvider->setCalcAverage(new CalculateMiddleValue);
    statsProvider->setUpdateScoreRange(new UpdateScoreRange);
    return statsProvider;
}
