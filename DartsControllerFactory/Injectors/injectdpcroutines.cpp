#include "injectdpcroutines.h"
#include "ServicesProvider/dcservices.h"
#include "DCInputServices/dcassembleinput.h"
#include "DPCServices/dpcinputevaluator.h"
#include "ModelsComCtxServices/dcaddinputtomodelscontext.h"
#include "DCTurnValuesServices/dccreateturnvalues.h"
#include "InitServices/dcinitializecontroller.h"
#include "ServiceRoutineServices/dcresetservices.h"

void InjectDPCRoutines::inject(DCServices *dc)
{
    injectInputRoutines(dc);
    injectOtherRoutines(dc);
    dc->setTurnValuesBuilder(new DCCreateTurnValues(dc));
}

void InjectDPCRoutines::injectInputRoutines(DCServices *dc)
{
    dc->setInputEvaluator(new DPCInputEvaluator(dc));
    dc->setUpdateModelsContext(new DCAddInputToModelsContext(dc));
    dc->setAssembleInput(new DCAssembleInput(dc));
}

void InjectDPCRoutines::injectOtherRoutines(DCServices *dc)
{
    dc->setInitializer(new DCInitializeController(dc));
    dc->setResetServices(new DCResetServices(dc));
}
