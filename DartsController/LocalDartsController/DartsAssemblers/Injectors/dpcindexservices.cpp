#include "dpcindexservices.h"

#include <DartsController/Contracts/Index/dcindexservices.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/LocalDartsController/Index/dcindexconverter.h>
#include <DartsController/LocalDartsController/Index/dpcindexcontroller.h>

void DPCIndexServices::inject(DCServices *dc) const
{
    auto indexServices = new DCIndexServices;
    indexServices->setIndexController(new DPCIndexController);
    indexServices->setIndexToByteArray(new DCIndexConverter);
    dc->setIndexServices(indexServices);
}
