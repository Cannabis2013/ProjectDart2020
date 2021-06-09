#include "builddartsscoreservicewithlocaljsondb.h"

using namespace DartsModelsContext;

BuildDartsScoreServiceWithLocalJsonDb::ServiceInterface *BuildDartsScoreServiceWithLocalJsonDb::buildModelsService() const
{
    auto service = DartsScoreModelsService::createInstance()
            ->setGetDartsScoreIndexesByModels(new GetDartsScoreIndexesByModel)
            ->setDartsScoreLessThanPredicate(new DartsScoreLessThanPredicate)
            ->setDartsInputsFilterService(new DartsInputsFilterService)
            ->setSortDartsInputModelsByPredicate(new InputModelsSortService)
            ->setSetInputHintService(new DartsInputModelHintService);
    return service;
}
