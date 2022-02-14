#include "injectdscroutines.h"
#include "ServicesProvider/dcservices.h"
#include "Routines/dcaddinputtomodelscontext.h"
#include "DCTurnValuesServices/dccreateturnvalues.h"
#include "InitServices/dcinitialize.h"
#include "Routines/dcresetservices.h"
#include "Routines/dccreatewinnerreport.h"

void InjectDSCRoutines::inject(DCServices *dc)
{
    auto routines = new DCRoutines;
    routines->setInitializer(new DCInitialize(dc));
    routines->setResetServices(new DCResetServices(dc));
    routines->setUpdateModelsContext(new DCAddInputToModelsContext(dc));
    routines->setCreateWinnerReport(new DCCreateWinnerReport(dc));
    dc->setRoutines(routines);
}
