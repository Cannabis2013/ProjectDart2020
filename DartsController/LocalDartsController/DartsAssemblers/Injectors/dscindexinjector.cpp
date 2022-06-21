#include "dscindexinjector.h"

#include <DartsController/Contracts/Index/dcindexservices.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/LocalDartsController/Index/dcindexconverter.h>
#include <DartsController/LocalDartsController/Index/dscindexcontroller.h>

void DSCIndexInjector::inject(DCServices *dc) const
{
    auto indexServices = new DCIndexServices;
    indexServices->setIndexToByteArray(new DCIndexConverter);
    indexServices->setIndexController(new DSCIndexController);
    dc->setIndexServices(indexServices);
}
