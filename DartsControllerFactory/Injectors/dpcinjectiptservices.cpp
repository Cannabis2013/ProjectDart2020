#include "dpcinjectiptservices.h"
#include "ServicesProvider/dcservices.h"
#include "DCInputSLAs/dcinputsservices.h"
#include "DCInputServices/dcjsontoinputmodels.h"
#include "DCInputServices/dcinputbuilder.h"
#include "DPCServices/dpcinputadder.h"
#include "DPCServices/dpcinputevaluator.h"
void DPCInjectIptServices::inject(DCServices *dc) const
{
    auto inputServices = new DCInputsServices;
    inputServices->setJsonToInputModels(new DCJsonToInputModels);
    inputServices->setInputConverter(new DCInputBuilder);
    inputServices->setInputAdder(new DPCInputAdder);
    inputServices->setInputEvaluator(new DPCInputEvaluator());
    dc->setInputServices(inputServices);
}
