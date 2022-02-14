#include "dscindexinjector.h"
#include "DCIndexSLAs/dcindexservices.h"
#include "ConverterServices/dcindexconverter.h"
#include "DSCIndex/dscindexcontroller.h"
#include "ServicesProvider/dcservices.h"

void DSCIndexInjector::inject(DCServices *dc) const
{
    auto indexServices = new DCIndexServices;
    indexServices->setIndexToByteArray(new DCIndexConverter);
    indexServices->setIndexController(new DSCIndexController);
    dc->setIndexServices(indexServices);
}
