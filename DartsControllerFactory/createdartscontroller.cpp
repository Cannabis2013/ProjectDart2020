#include "createdartscontroller.h"
#include "DartsAssemblers/createdpc.h"
#include "DartsAssemblers/createdsc.h"
CreateDartsController::CreateDartsController()
{
    assembleDPC = new CreateDPC;
    assembleDSC = new CreateDSC;
}

AbsDartsCtrl *CreateDartsController::pointCtrl()
{
    return assembleDPC->create();
}

AbsDartsCtrl *CreateDartsController::scoreCtrl()
{
    return assembleDSC->create();
}
