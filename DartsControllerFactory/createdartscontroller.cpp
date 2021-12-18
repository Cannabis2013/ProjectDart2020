#include "createdartscontroller.h"
#include "DartsAssemblers/createdpc.h"
#include "DartsAssemblers/createdsc.h"
AbsDartsCtrl *CreateDartsController::pointCtrl()
{
    return CreateDPC::create();
}

AbsDartsCtrl *CreateDartsController::scoreCtrl()
{
    return CreateDSC::create();
}
