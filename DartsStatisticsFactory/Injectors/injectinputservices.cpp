#include "injectinputservices.h"
#include "SLAs/servicesprovider.h"
#include "Inputs/jsontoinput.h"
#include "Inputs/inputsdb.h"
#include "Inputs/createinput.h"

void InjectInputServices::inject(ServicesProvider *provider)
{
    auto services = new InputServices;
    services->setJsonToInput(new JsonToInput);
    services->setInputsDb(new InputsDb);
    services->setCreateInput(new CreateInput);
    provider->setInputServices(services);
}
