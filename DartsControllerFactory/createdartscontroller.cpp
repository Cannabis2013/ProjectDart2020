#include "createdartscontroller.h"
#include "DartsAssemblers/assembledpc.h"
#include "DartsAssemblers/assembledsc.h"
CreateDartsController::CreateDartsController()
{
    assembleDPC = new AssembleDPC;
    assembleDSC = new AssembleDSC;
}

IDartsCtrl *CreateDartsController::pointCtrl()
{
    return assembleDPC->assemble();
}

IDartsCtrl *CreateDartsController::scoreCtrl()
{
    return assembleDSC->assemble();
}
