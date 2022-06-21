#include "injectstatsroutines.h"

#include <DartsStatistics/Contracts/Routines/routineservices.h>

#include <DartsStatistics/DartsStatisticsImp/Routines/createstatsreport.h>
#include <DartsStatistics/DartsStatisticsImp/Routines/removeinputfromcontext.h>
#include <DartsStatistics/DartsStatisticsImp/Routines/resetstatscontext.h>
#include <DartsStatistics/DartsStatisticsImp/Routines/updatecurrentstats.h>

RoutineServices *CreateStatsRoutines::create(ServicesContext *context)
{
        auto routineProvider = new RoutineServices();
        routineProvider->setUpdateStats(new UpdateCurrentStats(context));
        routineProvider->setResetContext(new ResetStatsContext(context));
        routineProvider->setCreateReport(new CreateStatsReport(context));
        routineProvider->setRemoveInputFromDb(new RemoveInputFromContext(context));
        return routineProvider;
}
