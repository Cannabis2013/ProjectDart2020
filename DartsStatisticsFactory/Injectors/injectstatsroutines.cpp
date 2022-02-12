#include "injectstatsroutines.h"
#include "SLAs/servicescontext.h"
#include "Routines/updatecurrentstats.h"
#include "Routines/resetstatscontext.h"
#include "Routines/createstatsreport.h"
#include "Routines/removeinputfromcontext.h"

RoutineServices *CreateStatsRoutines::create(ServicesContext *context)
{
    auto routineProvider = new RoutineServices();
    routineProvider->setUpdateStats(new UpdateCurrentStats(context));
    routineProvider->setResetContext(new ResetStatsContext(context));
    routineProvider->setCreateReport(new CreateStatsReport(context));
    routineProvider->setRemoveInputFromDb(new RemoveInputFromContext(context));
    return routineProvider;
}
