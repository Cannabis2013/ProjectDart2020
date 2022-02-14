#include "dscinputinjector.h"
#include "ServicesProvider/dcservices.h"
#include "Inputs/dcjsontoinputmodels.h"
#include "Inputs/dcinputbuilder.h"
#include "Inputs/dscinputadder.h"
#include "Inputs/dscinputevaluator.h"
#include "Inputs/dcinputconverter.h"

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
