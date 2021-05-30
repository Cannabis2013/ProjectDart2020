#include "localjsondbdartsscoreservicebuilder.h"

using namespace DartsModelsContext;

LocalJsonDbDartsScoreServiceBuilder::ServiceInterface *LocalJsonDbDartsScoreServiceBuilder::buildModelsService() const
{
    auto service = DartsScoreModelsService::createInstance()
            ->setGetDartsScoreIndexesByModels(new GetDartsScoreIndexesByModel)
            ->setDartsScoreLessThanPredicate(new DartsScoreLessThanPredicate)
            ->setDartsInputsFilterService(new DartsInputsFilterService)
            ->setRemoveModelsService(new RemoveModelsFromDbContext)
            ->setSortDartsInputModelsByPredicate(new SortPlayerInputsByPredicate)
            ->setSetInputHintService(new SetDartsInputHintService)
            ->setGetInputModelByIdService(new GetDartsInputModelById)
            ->setDbService(new DartsScoreJsonDb);
    return service;
}
