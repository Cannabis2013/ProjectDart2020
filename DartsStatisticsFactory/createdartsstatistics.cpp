#include "createdartsstatistics.h"
#include "Injectors/createstatisticprovider.h"
#include "Injectors/injectstatsroutines.h"
#include "Injectors/createsnapshotsprovider.h"
#include "dartsstatistics.h"
#include "Injectors/createstatsservices.h"
IDartsStatistics *CreateDartsStatistics::create() const
{
    auto context = new DartsStatistics;
    auto statisticServices = CreateStatisticProvider().create();
    auto snapShotsServices = CreateSnapShotsProvider().create();
    auto statsServices = CreateStatsServices().create();
    auto routines = CreateStatsRoutines().create(context);
    context->setStatisticServices(statisticServices);
    context->setSnapShotsServices(snapShotsServices);
    context->setStatsProvider(statsServices);
    context->setRoutines(routines);
    return context;
}
