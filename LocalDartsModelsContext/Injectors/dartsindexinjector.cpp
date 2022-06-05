#include "dartsindexinjector.h"
#include <DartsModelsContext/IndexesSLAs/dartsindexservices.h>
#include <DartsModelsContext/SLAs/dartsmodelsservices.h>
#include <LocalDartsModelsContext/IndexesServices/dartsindexbuilder.h>

void DartsIndexInjector::injectServices(DartsModelsServices *context)
{
    auto indexServices = new DartsIndexServices;
    indexServices->setIndexBuilder(new DartsIndexBuilder);
    context->setIndexServices(indexServices);
}
