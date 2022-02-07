#include "injectstatsservices.h"
#include "SLAs/servicescontext.h"

#include <Statistics/calculatemiddlevalue.h>

void InjectStatsServices::inject(ServicesContext *provider) const
{
    auto statsProvider = new StatsServices;
    statsProvider->setCalcAverage(new CalculateMiddleValue);
    provider->setStatsProvider(statsProvider);
}
