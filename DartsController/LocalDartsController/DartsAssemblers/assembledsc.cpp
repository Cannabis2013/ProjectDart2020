#include "assembledsc.h"

#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/dcinjectfinclient.h>
#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/dcinjectmetaclient.h>
#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/dscindexinjector.h>
#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/dscinjectplaservives.h>
#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/dscinputinjector.h>
#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/injectdscroutines.h>

#include <DartsController/LocalDartsController/Controller/dartscontroller.h>

AssembleDSC::AssembleDSC()
{
        finInjector = new DCInjectFinClient;
        metaInjector = new DCInjectMetaClient;
        plaCtxInjector = new DSCInjectPlaServives;
        indexInjector = new DSCIndexInjector;
        inputInjector = new DSCInputInjector;
        injectRoutines = new InjectDSCRoutines;
}

DartsController *AssembleDSC::assemble(AbstractDartsContext *modelsContext)
{
        auto dc = new DartsController;
        dc->setModelsContext(modelsContext);
        finInjector->inject(dc);
        metaInjector->inject(dc);
        plaCtxInjector->inject(dc);
        indexInjector->inject(dc);
        inputInjector->inject(dc);
        injectRoutines->inject(dc);
        return dc;
}
