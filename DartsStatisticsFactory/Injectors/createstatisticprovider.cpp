#include "createstatisticprovider.h"

#include <DartsStatistics/Players/statisticservices.h>

#include <DartsStatisticsFactory/Players/createstatmodel.h>
#include <DartsStatisticsFactory/Players/statsmemory.h>

StatisticServices *CreateStatisticProvider::create()
{
        auto services = new StatisticServices;
        services->setStatisticsDb(new StatsMemory);
        services->setCreateStatistic(new CreateStatModel);
        return services;
}
