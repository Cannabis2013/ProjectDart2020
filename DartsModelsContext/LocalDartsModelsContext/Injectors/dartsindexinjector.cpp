#include "dartsindexinjector.h"
#include <DartsModelsContext/Contracts/Index/dartsindexservices.h>
#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <DartsModelsContext/LocalDartsModelsContext/IndexesServices/dartsindexbuilder.h>

void DartsIndexInjector::injectServices(DartsModelsServices *context)
{
    auto indexServices = new DartsIndexServices;
    indexServices->setIndexBuilder(new DartsIndexBuilder);
    context->setIndexServices(indexServices);
}
