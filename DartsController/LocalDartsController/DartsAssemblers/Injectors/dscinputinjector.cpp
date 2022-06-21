#include "dscinputinjector.h"

#include <DartsController/Contracts/Inputs/dcinputsservices.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/LocalDartsController/Inputs/dcinputbuilder.h>
#include <DartsController/LocalDartsController/Inputs/dcinputconverter.h>
#include <DartsController/LocalDartsController/Inputs/dcjsontoinputmodels.h>
#include <DartsController/LocalDartsController/Inputs/dscinputadder.h>
#include <DartsController/LocalDartsController/Inputs/dscinputevaluator.h>

void DSCInputInjector::inject(DCServices *dc)
{
    auto inputServices = new DCInputsServices;
    inputServices->setJsonToInputModels(new DCJsonToInputModels);
    inputServices->setCreateInputModel(new DCInputBuilder);
    inputServices->setInputConverter(new DCInputConverter);
    inputServices->setInputAdder(new DSCInputAdder);
    inputServices->setInputEvaluator(new DSCInputEvaluator);
    dc->setInputServices(inputServices);

}
