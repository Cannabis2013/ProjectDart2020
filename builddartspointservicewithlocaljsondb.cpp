#include "builddartspointservicewithlocaljsondb.h"

using namespace DartsModelsContext;

BuildDartsPointServiceWithLocalJsonDb::ServiceInterface *DartsModelsContext::BuildDartsPointServiceWithLocalJsonDb::buildModelsService() const
{

    auto pointModelsService = DartsPointModelsService::createInstance()
            ->setDartsInputsFilterService(new DartsInputsFilterService)
            ->setAssembleDartsPointIndexes(new DartsSingleAttemptIndexesBuilder)
            ->setDartsInputHintService(new DartsInputModelHintService);
    return pointModelsService;
}
