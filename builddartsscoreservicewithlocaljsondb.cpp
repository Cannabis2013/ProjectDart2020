#include "builddartsscoreservicewithlocaljsondb.h"

using namespace DartsModelsContext;

BuildDartsScoreServiceWithLocalJsonDb::ServiceInterface *BuildDartsScoreServiceWithLocalJsonDb::buildModelsService() const
{
    auto service = DartsScoreModelsService::createInstance()
            ->setGetDartsScoreIndexesByModels(new GetDartsScoreIndexesByModel)
            ->setDartsScoreLessThanPredicate(new DartsScoreLessThanPredicate)
            ->setDartsInputsFilterService(new DartsInputsFilterService)
            ->setRemoveModelsService(new RemoveModelsFromDbContext)
            ->setSortDartsInputModelsByPredicate(new SortPlayerInputsByPredicate)
            ->setSetInputHintService(new DartsInputModelHintService)
            ->setGetInputModelByIdService(new GetDartsInputModelById)
            ->setDbService(new DartsScoreJsonDb);
    return service;
}
