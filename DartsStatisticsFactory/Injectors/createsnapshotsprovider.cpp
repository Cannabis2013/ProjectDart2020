#include "createsnapshotsprovider.h"
#include "SLAs/servicescontext.h"
#include "Inputs/jsontosnapshot.h"
#include "Inputs/inputsdb.h"
#include "Inputs/createinput.h"

SnapShotsServices *CreateSnapShotsProvider::create()
{
    auto services = new SnapShotsServices;
    services->setJsonToInput(new JsonToSnapShot);
    services->setInputsDb(new InputsDb);
    services->setCreateInput(new CreateInput);
    return services;
}
