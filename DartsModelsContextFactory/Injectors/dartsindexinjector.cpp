#include "dartsindexinjector.h"
#include "IndexesSLAs/dartsindexslas.h"
#include "IndexesServices/dartsindexbuilder.h"
#include "IndexesServices/updatedartsindexes.h"
void DartsIndexInjector::injectServices(DartsIndexSLAs *context)
{
    context->setUpdateIndexes(new UpdateDartsIndexes);
    context->setIndexBuilder(new DartsIndexBuilder);
}
