#include "injectdscroutines.h"
#include "ServicesProvider/dcservices.h"
#include "Routines/dcaddinputtomodelscontext.h"
#include "Init/dcinitialize.h"
#include "Routines/dcresetservices.h"
#include "Routines/dccreatewinnerreport.h"
#include "Routines/dcgetturnvaluesasjson.h"
#include "Routines/dcgetscoresasjson.h"

void InjectDSCRoutines::inject(DCServices *dc)
{
    auto routines = new DCRoutines;
    routines->setInitializer(new DCInitialize(dc));
    routines->setResetServices(new DCResetServices(dc));
    routines->setUpdateModelsContext(new DCAddInputToModelsContext(dc));
    routines->setCreateWinnerReport(new DCCreateWinnerReport(dc));
    routines->setGetTurnValuesAsJson(new DCGetTurnValuesAsJson(dc));
    routines->setGetScoresAsJson(new DCGetScoresAsJson(dc));
    dc->setRoutines(routines);
}
