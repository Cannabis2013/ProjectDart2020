#include "assembledsc.h"
#include "Injectors/dscinjectplaservives.h"
#include "Injectors/dscindexinjector.h"
#include "Injectors/dscinputinjector.h"
#include "Injectors/dcinjectmetaclient.h"
#include "Injectors/dcinjectfinclient.h"
#include "Controller/dartscontroller.h"
#include "Injectors/injectdscroutines.h"

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
