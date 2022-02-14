#include "injectdpcroutines.h"
#include "ServicesProvider/dcservices.h"
#include "Routines/dcaddinputtomodelscontext.h"
#include "DCTurnValuesServices/dccreateturnvalues.h"
#include "InitServices/dcinitialize.h"
#include "Routines/dccreatewinnerreport.h"
#include "Routines/dcresetservices.h"

void InjectDPCRoutines::inject(DCServices *dc)
{
    auto routines = new DCRoutines;
    routines->setUpdateModelsContext(new DCAddInputToModelsContext(dc));
    routines->setInitializer(new DCInitialize(dc));
    routines->setResetServices(new DCResetServices(dc));
    routines->setCreateWinnerReport(new DCCreateWinnerReport(dc));
    dc->setRoutines(routines);
}
