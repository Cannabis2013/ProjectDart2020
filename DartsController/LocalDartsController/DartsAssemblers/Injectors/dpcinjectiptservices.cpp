#include "dpcinjectiptservices.h"

#include <DartsController/Contracts/Inputs/dcinputsservices.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/LocalDartsController/Inputs/dcinputbuilder.h>
#include <DartsController/LocalDartsController/Inputs/dcinputconverter.h>
#include <DartsController/LocalDartsController/Inputs/dcjsontoinputmodels.h>
#include <DartsController/LocalDartsController/Inputs/dpcinputadder.h>
#include <DartsController/LocalDartsController/Inputs/dpcinputevaluator.h>

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
