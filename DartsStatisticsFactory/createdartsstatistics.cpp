#include "createdartsstatistics.h"
#include "Injectors/createstatisticprovider.h"
#include "Injectors/injectstatsroutines.h"
#include "Injectors/createsnapshotsprovider.h"
#include "Injectors/createstatsservices.h"
#include <DartsStatistics/dartsstatistics.h>

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
