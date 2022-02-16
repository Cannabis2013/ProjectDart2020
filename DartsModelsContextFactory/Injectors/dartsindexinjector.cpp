#include "dartsindexinjector.h"
#include "IndexesSLAs/dartsindexservices.h"
#include "IndexesServices/dartsindexbuilder.h"
#include "SLAs/dartsmodelsservices.h"
void DartsIndexInjector::injectServices(DartsModelsServices *context)
{
    auto idxServices = new DartsIndexServices;
    idxServices->setIndexBuilder(new DartsIndexBuilder);
    context->setIndexServices(idxServices);
}
