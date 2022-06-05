#include "dscindexinjector.h"

#include <DartsController/Index/dcindexservices.h>
#include <LocalDartsController/Index/dcindexconverter.h>
#include <LocalDartsController/Index/dscindexcontroller.h>
#include <DartsController/ServicesProvider/dcservices.h>

void DSCIndexInjector::inject(DCServices *dc) const
{
    auto indexServices = new DCIndexServices;
    indexServices->setIndexToByteArray(new DCIndexConverter);
    indexServices->setIndexController(new DSCIndexController);
    dc->setIndexServices(indexServices);
}
