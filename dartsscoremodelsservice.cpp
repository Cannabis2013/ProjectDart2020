#include "dartsscoremodelsservice.h"

using namespace DartsModelsContext;

DartsScoreModelsService *DartsScoreModelsService::createInstance()
{
    return new DartsScoreModelsService;
}

const DartsScoreModelsService::PlayerInput *DartsScoreModelsService::dartsScoreModel(const QUuid &tournamentId,
                                                                                     const QUuid &playerId,
                                                                                     const int &roundIndex,
                                                                                     const DbModelsService *dbService) const
{
    auto inputs = dbService->models();
    auto filteredInputs = _dartsInputsFilterService->filterByRoundIndex(inputs,tournamentId,playerId,roundIndex);
    auto input = filteredInputs.first();
    return input;
}

void DartsScoreModelsService::setDartsScoreHint(const PlayerInput *model, const int &hint, DbModelsService *dbService)
{
    _setInputHintService->service(model,hint);
    dbService->saveState();
}

const IDartsScoreIndexes *DartsScoreModelsService::dartsScoreIndexes(const QUuid &tournamentId, const int &assignedPlayersCount, const DbModelsService *dbService) const
{
    auto dartsScoreInputs = _dartsInputsFilterService->filterByHint(dbService->models(),tournamentId,DisplayHint);
    auto orderedPlayerInputs = _sortDartsInputModelsByPredicate->service(dartsScoreInputs,_dartsScoreLessThanPredicate);
    auto indexes = _getDartsScoreIndexesByModels->buildIndexes(orderedPlayerInputs,assignedPlayersCount);
    return indexes;
}

DartsScoreModelsService *DartsScoreModelsService::setDartsInputsFilterService(FilterDartsInputsService *newDartsInputsFilterService)
{
    _dartsInputsFilterService = newDartsInputsFilterService;
    return this;
}

DartsScoreModelsService *DartsScoreModelsService::setSetInputHintService(setInputHintService *newSetInputHintService)
{
    _setInputHintService = newSetInputHintService;
    return this;
}

DartsScoreModelsService *DartsScoreModelsService::setSortDartsInputModelsByPredicate(SortDartsInputsByPredicateService *newSortDartsInputModelsByPredicate)
{
    _sortDartsInputModelsByPredicate = newSortDartsInputModelsByPredicate;
    return this;
}

DartsScoreModelsService *DartsScoreModelsService::setGetDartsScoreIndexesByModels(GetScoreIndexesByModels *newGetDartsScoreIndexesByModels)
{
    _getDartsScoreIndexesByModels = newGetDartsScoreIndexesByModels;
    return this;
}

DartsScoreModelsService *DartsScoreModelsService::setDartsScoreLessThanPredicate(Predicate *newDartsPointLessThanPredicate)
{
    _dartsScoreLessThanPredicate = newDartsPointLessThanPredicate;
    return this;
}
