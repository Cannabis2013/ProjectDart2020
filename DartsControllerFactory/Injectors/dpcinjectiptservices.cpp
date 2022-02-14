#include "dpcinjectiptservices.h"
#include "ServicesProvider/dcservices.h"
#include "Inputs/dcinputsservices.h"
#include "Inputs/dcjsontoinputmodels.h"
#include "Inputs/dcinputbuilder.h"
#include "Inputs/dpcinputadder.h"
#include "Inputs/dpcinputevaluator.h"
#include "Inputs/dcinputconverter.h"
void DPCInjectIptServices::inject(DCServices *dc) const
{
    auto inputServices = new DCInputsServices;
    inputServices->setJsonToInputModels(new DCJsonToInputModels);
    inputServices->setCreateInputModel(new DCInputBuilder);
    inputServices->setInputAdder(new DPCInputAdder);
    inputServices->setInputEvaluator(new DPCInputEvaluator());
    inputServices->setInputConverter(new DCInputConverter);
    dc->setInputServices(inputServices);
}
