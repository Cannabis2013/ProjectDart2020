#include "dpcindexservices.h"

#include <DartsController/Index/dcindexservices.h>
#include <DartsController/ServicesProvider/dcservices.h>
#include <LocalDartsController/Index/dcindexconverter.h>
#include <LocalDartsController/Index/dpcindexcontroller.h>

void DPCIndexServices::inject(DCServices *dc) const
{
    auto indexServices = new DCIndexServices;
    indexServices->setIndexController(new DPCIndexController);
    indexServices->setIndexToByteArray(new DCIndexConverter);
    dc->setIndexServices(indexServices);
}
