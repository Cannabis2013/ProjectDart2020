#include "createdsc.h"
#include "Injectors/dscinjectplaservives.h"
#include "Injectors/dscindexinjector.h"
#include "Injectors/dscinputinjector.h"
#include "Injectors/dscjsonresponseinjector.h"
#include "Injectors/dscstatsinjector.h"
#include "Injectors/dcinjectmetaclient.h"
#include "Injectors/dcinjectfinclient.h"
#include "dartscontroller.h"
#include "DSCServices/dscvaluesbuilder.h"
CreateDSC::CreateDSC()
{
    finInjector = new DCInjectFinClient;
    metaInjector = new DCInjectMetaClient;
    plaCtxInjector = new DSCInjectPlaServives;
    indexInjector = new DSCIndexInjector;
    inputInjector = new DSCInputInjector;
    jsonInjector = new DSCJsonResponseInjector;
    statsInjector = new DSCStatsInjector;
}

AbsDartsCtrl *CreateDSC::create()
{
    auto dc = new DartsController;
    finInjector->inject(dc);
    metaInjector->inject(dc);
    plaCtxInjector->inject(dc);
    indexInjector->inject(dc);
    inputInjector->inject(dc);
    jsonInjector->inject(dc);
    statsInjector->inject(dc);
    dc->setTurnValuesBuilder(new DSCValuesBuilder);
    return dc;
}
