#include "builddartspointservicewithlocaljsondb.h"

using namespace DartsModelsContext;

BuildDartsPointServiceWithLocalJsonDb::ServiceInterface *DartsModelsContext::BuildDartsPointServiceWithLocalJsonDb::buildModelsService() const
{
    auto dartsPointDb = DartsPointJsonDbService::createInstance(new AssembleSingleAttemptPointsFromJson,
                                                            new AssembleJsonArrayFromDartsPoints);

    auto pointModelsService = DartsPointModelsService::createInstance()
            ->setDartsInputsFilterService(new DartsInputsFilterService)
            ->setAssembleDartsPointIndexes(new DartsSingleAttemptIndexesBuilder)
            ->setSortDartsInputModelsByPredicate(new SortPlayerInputsByPredicate)
            ->setDartsSortingPredicate(new DartsPointLessThanPredicate)
            ->setGetInputModelByIdService(new GetDartsInputModelById)
            ->setRemoveModelsService(new RemoveModelsFromDbContext)
            ->setDartsInputHintService(new DartsInputModelHintService)
            ->setDbService(dartsPointDb);
    return pointModelsService;
}
