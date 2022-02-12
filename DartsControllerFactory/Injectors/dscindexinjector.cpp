#include "dscindexinjector.h"
#include "DCIndexSLAs/dcindexslas.h"
#include "ConverterServices/dcindexconverter.h"
#include "IndexServices/dscindexcontroller.h"

void DSCIndexInjector::inject(DCIndexSLAs *dc) const
{
    dc->setIndexToByteArray(new DCIndexConverter);
    dc->setIndexController(new DSCIndexController);
}
