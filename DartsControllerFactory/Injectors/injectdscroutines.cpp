#include "injectdscroutines.h"
#include "ServicesProvider/dcservices.h"
#include "DSCServices/dscinputevaluator.h"
#include "ModelsComCtxServices/dcaddinputtomodelscontext.h"
#include "DCTurnValuesServices/dccreateturnvalues.h"
#include "InitServices/dcinitialize.h"
#include "Routines/dcresetservices.h"

void InjectDSCRoutines::inject(DCServices *dc)
{
    auto routines = new DCRoutines;
    routines->setInitializer(new DCInitialize(dc));
    routines->setResetServices(new DCResetServices(dc));
    routines->setInputEvaluator(new DSCInputEvaluator(dc));
    routines->setUpdateModelsContext(new DCAddInputToModelsContext(dc));
    auto turnValuesServices = new DCTurnValuesServices;
    turnValuesServices->setTurnValuesBuilder(new DCCreateTurnValues(dc));
    dc->setTurnValsServices(turnValuesServices);
    dc->setRoutines(routines);
}
