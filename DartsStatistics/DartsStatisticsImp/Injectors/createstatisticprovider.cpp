#include "createstatisticprovider.h"

#include <DartsStatistics/Contracts/Players/statisticservices.h>

#include <DartsStatistics/DartsStatisticsImp/Players/createstatmodel.h>
#include <DartsStatistics/DartsStatisticsImp/Players/statsmemory.h>

StatisticServices *CreateStatisticProvider::create()
{
        auto services = new StatisticServices;
        services->setStatisticsDb(new StatsMemory);
        services->setCreateStatistic(new CreateStatModel);
        return services;
}
