#include "dpcinjectidxservices.h"
#include "DCIndexSLAs/dcindexslas.h"
#include "IndexServices/dpcindexcontroller.h"
#include "ConverterServices/dcindexconverter.h"

void DPCInjectIdxServices::inject(DCIndexSLAs *dc) const
{
    dc->setIndexController(new DPCIndexController);
    dc->setIndexToByteArray(new DCIndexConverter);
}
