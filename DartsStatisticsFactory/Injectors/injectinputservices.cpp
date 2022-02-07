#include "injectinputservices.h"
#include "SLAs/servicescontext.h"
#include "Inputs/jsontoinput.h"
#include "Inputs/inputsdb.h"
#include "Inputs/createinput.h"

void InjectInputServices::inject(ServicesContext *provider)
{
    auto services = new InputServices;
    services->setJsonToInput(new JsonToInput);
    services->setInputsDb(new InputsDb);
    services->setCreateInput(new CreateInput);
    provider->setInputServices(services);
}
