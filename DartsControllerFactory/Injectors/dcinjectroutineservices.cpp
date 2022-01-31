#include "dcinjectroutineservices.h"
#include "InitServices/dcinitializecontroller.h"
#include "ServicesProvider/dcservices.h"
#include "ServiceRoutineServices/dcresetservices.h"

void DCInjectRoutineServices::inject(DCServices *dc) const
{
    dc->setInitializer(new DCInitializeController(dc));
    dc->setResetServices(new DCResetServices(dc));
}
