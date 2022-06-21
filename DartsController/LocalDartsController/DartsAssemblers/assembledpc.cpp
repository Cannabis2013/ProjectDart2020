#include "assembledpc.h"

#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/dcinjectfinclient.h>
#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/dcinjectmetaclient.h>
#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/dpcindexservices.h>
#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/dpcinjectiptservices.h>
#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/dpcinjectplaservices.h>
#include <DartsController/LocalDartsController/DartsAssemblers/Injectors/injectdpcroutines.h>
#include <DartsController/LocalDartsController/Controller/dartscontroller.h>

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
