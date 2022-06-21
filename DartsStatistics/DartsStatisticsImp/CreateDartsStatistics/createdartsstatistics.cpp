#include "createdartsstatistics.h"
#include "dartsstatistics.h"

#include <DartsStatistics/DartsStatisticsImp/Injectors/createsnapshotsprovider.h>
#include <DartsStatistics/DartsStatisticsImp/Injectors/createstatisticprovider.h>
#include <DartsStatistics/DartsStatisticsImp/Injectors/createstatsservices.h>
#include <DartsStatistics/DartsStatisticsImp/Injectors/injectstatsroutines.h>

IDartsStatistics *CreateDartsStatistics::create() const
{
        auto context = new DartsStatistics;
        auto statisticServices = CreateStatisticProvider().create();
        auto snapShotsServices = CreateSnapShotsProvider().create();
        auto statsServices = CreateStatsServices().create();
        context->setStatisticServices(statisticServices);
        context->setSnapShotsServices(snapShotsServices);
        context->setStatsProvider(statsServices);
        auto routines = CreateStatsRoutines().create(context);
        context->setRoutines(routines);
        return context;
}
