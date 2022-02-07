#include "injectstatsroutines.h"
#include "SLAs/servicescontext.h"
#include "Routines/bytearraytoinputs.h"
#include "Routines/updateplayerstats.h"
#include "Routines/resetstatscontext.h"
#include "Routines/createstatsreport.h"
#include "Routines/removeinputfromcontext.h"

void InjectStatsRoutines::inject(ServicesContext *services)
{
    auto routineProvider = new RoutineServices();
    routineProvider->setConvertToInputs(new ByteArrayToInputs(services));
    routineProvider->setUpdateStats(new UpdatePlayerStats(services));
    routineProvider->setResetContext(new ResetStatsContext(services));
    routineProvider->setCreateReport(new CreateStatsReport(services));
    routineProvider->setRemoveInputFromDb(new RemoveInputFromContext(services));
    services->setRoutines(routineProvider);
}
