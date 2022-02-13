#include "injectdpcroutines.h"
#include "ServicesProvider/dcservices.h"
#include "DPCServices/dpcinputevaluator.h"
#include "ModelsComCtxServices/dcaddinputtomodelscontext.h"
#include "DCTurnValuesServices/dccreateturnvalues.h"
#include "InitServices/dcinitialize.h"

#include <Routines/dcresetservices.h>

void InjectDPCRoutines::inject(DCServices *dc)
{
    auto routines = new DCRoutines;
    routines->setInputEvaluator(new DPCInputEvaluator(dc));
    routines->setUpdateModelsContext(new DCAddInputToModelsContext(dc));
    routines->setInitializer(new DCInitialize(dc));
    routines->setResetServices(new DCResetServices(dc));
    dc->setRoutines(routines);
}
