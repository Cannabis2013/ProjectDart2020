#include "assembledpc.h"

#include <LocalDartsController/Injectors/dcinjectfinclient.h>
#include <LocalDartsController/Injectors/dcinjectmetaclient.h>
#include <LocalDartsController/Injectors/dpcindexservices.h>
#include <LocalDartsController/Injectors/dpcinjectiptservices.h>
#include <LocalDartsController/Injectors/dpcinjectplaservices.h>
#include <LocalDartsController/Injectors/injectdpcroutines.h>
#include <DartsController/Controller/dartscontroller.h>

AssembleDPC::AssembleDPC()
{
    injectFinServices = new DCInjectFinClient;
    injectMetaServices = new DCInjectMetaClient;
    injectPlaServices = new DPCInjectPlaServices;
    injectIptServices = new DPCInjectIptServices;
    injectIdxServices = new DPCIndexServices;
    injectRoutines = new InjectDPCRoutines;
}

DartsController *AssembleDPC::assemble(AbstractDartsContext *modelsContext)
{
        auto dc = new DartsController;
        dc->setModelsContext(modelsContext);
        injectFinServices->inject(dc);
        injectMetaServices->inject(dc);
        injectPlaServices->inject(dc);
        injectIptServices->inject(dc);
        injectIdxServices->inject(dc);
        injectRoutines->inject(dc);
        return dc;
}
