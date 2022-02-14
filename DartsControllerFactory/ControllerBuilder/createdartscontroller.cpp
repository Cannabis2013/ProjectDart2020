#include "createdartscontroller.h"
#include "DartsAssemblers/assembledpc.h"
#include "DartsAssemblers/assembledsc.h"
#include "Controller/dartscontroller.h"

CreateDartsController::CreateDartsController()
{
    assembleDPC = new AssembleDPC;
    assembleDSC = new AssembleDSC;
}

IDartsCtrl *CreateDartsController::pointCtrl(AbsDartsCtx *modelsContext)
{
    auto dpc = assembleDPC->assemble(modelsContext);
    return dpc;
}

IDartsCtrl *CreateDartsController::scoreCtrl(AbsDartsCtx *modelsContext)
{
    auto dsc = assembleDSC->assemble(modelsContext);
    return dsc;
}
