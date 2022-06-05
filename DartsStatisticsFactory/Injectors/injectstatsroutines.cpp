#include "injectstatsroutines.h"

#include <DartsStatistics/Routines/routineservices.h>

#include <DartsStatisticsFactory/Routines/createstatsreport.h>
#include <DartsStatisticsFactory/Routines/removeinputfromcontext.h>
#include <DartsStatisticsFactory/Routines/resetstatscontext.h>
#include <DartsStatisticsFactory/Routines/updatecurrentstats.h>

RoutineServices *CreateStatsRoutines::create(ServicesContext *context)
{
        auto routineProvider = new RoutineServices();
        routineProvider->setUpdateStats(new UpdateCurrentStats(context));
        routineProvider->setResetContext(new ResetStatsContext(context));
        routineProvider->setCreateReport(new CreateStatsReport(context));
        routineProvider->setRemoveInputFromDb(new RemoveInputFromContext(context));
        return routineProvider;
}
