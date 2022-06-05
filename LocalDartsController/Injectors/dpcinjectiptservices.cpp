#include "dpcinjectiptservices.h"

#include <DartsController/Inputs/dcinputsservices.h>

#include <LocalDartsController/Inputs/dcinputbuilder.h>
#include <LocalDartsController/Inputs/dcinputconverter.h>
#include <LocalDartsController/Inputs/dcjsontoinputmodels.h>
#include <LocalDartsController/Inputs/dpcinputadder.h>
#include <LocalDartsController/Inputs/dpcinputevaluator.h>
#include <DartsController/ServicesProvider/dcservices.h>

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
