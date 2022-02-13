#include "dscinputinjector.h"
#include "ServicesProvider/dcservices.h"
#include "DCInputServices/dcjsontoinputmodels.h"
#include "DCInputServices/dcinputbuilder.h"
#include "DSCServices/dscinputadder.h"

void DSCInputInjector::inject(DCServices *dc)
{
    auto inputServices = new DCInputsServices;
    inputServices->setJsonToInputModels(new DCJsonToInputModels);
    inputServices->setInputConverter(new DCInputBuilder);
    inputServices->setInputAdder(new DSCInputAdder);
    dc->setInputServices(inputServices);

}
