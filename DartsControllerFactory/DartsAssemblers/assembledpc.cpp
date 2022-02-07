#include "assembledpc.h"
#include "dartscontroller.h"
#include "Injectors/dcinjectfinclient.h"
#include "Injectors/dcinjectmetaclient.h"
#include "Injectors/dpcinjectplaservices.h"
#include "Injectors/dpcinjectiptservices.h"
#include "Injectors/dpcinjectidxservices.h"
#include "Injectors/dpcinjectstatsservices.h"
#include "Injectors/injectdpcroutines.h"

AssembleDPC::AssembleDPC()
{
    injectFinServices = new DCInjectFinClient;
    injectMetaServices = new DCInjectMetaClient;
    injectPlaServices = new DPCInjectPlaServices;
    injectIptServices = new DPCInjectIptServices;
    injectIdxServices = new DPCInjectIdxServices;
    injectStatsServices = new DPCInjectStatsServices;
    injectRoutines = new InjectDPCRoutines;
}

IDartsCtrl *AssembleDPC::assemble()
{
    auto dc = new DartsController;
    injectFinServices->inject(dc);
    injectMetaServices->inject(dc);
    injectPlaServices->inject(dc);
    injectIptServices->inject(dc);
    injectIdxServices->inject(dc);
    injectStatsServices->inject(dc);
    injectRoutines->inject(dc);
    return dc;
}