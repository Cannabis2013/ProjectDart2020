#include "createsnapshotsprovider.h"
#include "SLAs/servicescontext.h"
#include "Inputs/inputsdb.h"
#include "Inputs/createinput.h"

SnapShotsServices *CreateSnapShotsProvider::create()
{
    auto services = new SnapShotsServices;
    services->setSnapShotsDb(new InputsDb);
    services->setCreateSnapShot(new CreateInput);
    return services;
}
