#include "dpcinjectidxservices.h"
#include "DCIndexSLAs/dcindexservices.h"
#include "IndexServices/dpcindexcontroller.h"
#include "ConverterServices/dcindexconverter.h"
#include "ServicesProvider/dcservices.h"

void DPCInjectIdxServices::inject(DCServices *dc) const
{
    auto indexServices = new DCIndexServices;
    indexServices->setIndexController(new DPCIndexController);
    indexServices->setIndexToByteArray(new DCIndexConverter);
    dc->setIndexServices(indexServices);
}
