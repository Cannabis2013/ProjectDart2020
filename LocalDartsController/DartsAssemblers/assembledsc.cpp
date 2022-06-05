#include "assembledsc.h"

#include <LocalDartsController/Injectors/dcinjectfinclient.h>
#include <LocalDartsController/Injectors/dcinjectmetaclient.h>
#include <LocalDartsController/Injectors/dscindexinjector.h>
#include <LocalDartsController/Injectors/dscinjectplaservives.h>
#include <LocalDartsController/Injectors/dscinputinjector.h>
#include <LocalDartsController/Injectors/injectdscroutines.h>
#include <DartsController/Controller/dartscontroller.h>

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
