#include "dscinputinjector.h"

#include <DartsController/Inputs/dcinputsservices.h>
#include <LocalDartsController/Inputs/dcinputbuilder.h>
#include <LocalDartsController/Inputs/dcinputconverter.h>
#include <LocalDartsController/Inputs/dcjsontoinputmodels.h>
#include <LocalDartsController/Inputs/dscinputadder.h>
#include <LocalDartsController/Inputs/dscinputevaluator.h>
#include <DartsController/ServicesProvider/dcservices.h>

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
