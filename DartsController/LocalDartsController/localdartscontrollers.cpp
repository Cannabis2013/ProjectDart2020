#include "localdartscontrollers.h"

#include <DartsController/LocalDartsController/DartsAssemblers/assembledpc.h>
#include <DartsController/LocalDartsController/DartsAssemblers/assembledsc.h>
#include <DartsController/LocalDartsController/Controller/dartscontroller.h>

IDartsCtrl *LocalDartsControllers::singlePoint(AbstractDartsContext *modelsContext)
{
        auto assembler = new AssembleDPC;
        auto dpc = assembler->assemble(modelsContext);
        return dpc;
}

IDartsCtrl *LocalDartsControllers::multiPoint(AbstractDartsContext *modelsContext)
{
        auto assembler = new AssembleDSC;
        auto dsc = assembler->assemble(modelsContext);
        return dsc;
}
