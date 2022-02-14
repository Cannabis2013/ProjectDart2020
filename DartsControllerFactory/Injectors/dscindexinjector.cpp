#include "dscindexinjector.h"
#include "Index/dcindexservices.h"
#include "Index/dcindexconverter.h"
#include "Index/dscindexcontroller.h"
#include "ServicesProvider/dcservices.h"

void DSCIndexInjector::inject(DCServices *dc) const
{
    auto indexServices = new DCIndexServices;
    indexServices->setIndexToByteArray(new DCIndexConverter);
    indexServices->setIndexController(new DSCIndexController);
    dc->setIndexServices(indexServices);
}
