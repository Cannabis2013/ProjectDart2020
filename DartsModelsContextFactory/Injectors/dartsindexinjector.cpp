#include "dartsindexinjector.h"
#include "IndexesSLAs/dartsindexservices.h"
#include "IndexesServices/dartsindexbuilder.h"
#include "SLAs/dmcservices.h"
void DartsIndexInjector::injectServices(DMCServices *context)
{
    auto idxServices = new DartsIndexServices;
    idxServices->setIndexBuilder(new DartsIndexBuilder);
    context->setIndexServices(idxServices);
}
