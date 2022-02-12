#include "createstatisticprovider.h"
#include "SLAs/servicescontext.h"
#include "Players/statsmemory.h"
#include "Players/createstatmodel.h"
StatisticServices *CreateStatisticProvider::create()
{
    auto services = new StatisticServices;
    services->setStatisticsDb(new StatsMemory);
    services->setCreateStatistic(new CreateStatModel);
    return services;
}
