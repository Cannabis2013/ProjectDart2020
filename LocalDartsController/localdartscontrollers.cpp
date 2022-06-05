#include "localdartscontrollers.h"

#include <LocalDartsController/DartsAssemblers/assembledpc.h>
#include <LocalDartsController/DartsAssemblers/assembledsc.h>
#include <DartsController/Controller/dartscontroller.h>

LocalDartsControllers::LocalDartsControllers()
{
        assembleDPC = new AssembleDPC;
        assembleDSC = new AssembleDSC;
}

IDartsCtrl *LocalDartsControllers::singlePoint(AbstractDartsContext *modelsContext)
{
        auto dpc = assembleDPC->assemble(modelsContext);
        return dpc;
}

IDartsCtrl *LocalDartsControllers::multiPoint(AbstractDartsContext *modelsContext)
{
        auto dsc = assembleDSC->assemble(modelsContext);
        return dsc;
}
