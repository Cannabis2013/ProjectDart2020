#include "dpcinjectidxservices.h"
#include "Index/dcindexservices.h"
#include "Index/dpcindexcontroller.h"
#include "Index/dcindexconverter.h"
#include "ServicesProvider/dcservices.h"

void DPCInjectIdxServices::inject(DCServices *dc) const
{
    auto indexServices = new DCIndexServices;
    indexServices->setIndexController(new DPCIndexController);
    indexServices->setIndexToByteArray(new DCIndexConverter);
    dc->setIndexServices(indexServices);
}
