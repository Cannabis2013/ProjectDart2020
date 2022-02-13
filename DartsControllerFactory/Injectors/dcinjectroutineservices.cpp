#include "dcinjectroutineservices.h"
#include "InitServices/dcinitialize.h"
#include "ServicesProvider/dcservices.h"
#include "Routines/dcresetservices.h"

void DCInjectRoutineServices::inject(DCServices *dc) const
{
    auto routineServices = new DCRoutines;
    routineServices->setInitializer(new DCInitialize(dc));
    routineServices->setResetServices(new DCResetServices(dc));
    dc->setRoutines(routineServices);
}
