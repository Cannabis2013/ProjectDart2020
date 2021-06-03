#include "dartsscoremodelsservice.h"

using namespace DartsModelsContext;

DartsScoreModelsService *DartsScoreModelsService::createInstance()
{
    return new DartsScoreModelsService;
}

const IDartsScoreModelsService::PlayerInput *DartsScoreModelsService::dartsScoreModel(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) const
{
    auto scoreInputs = _dartsScoresDb->models();
    auto scoreModelsByRoundIndex = _dartsInputsFilterService->filterByRoundIndex(scoreInputs,tournamentId,playerId,roundIndex);
    auto model = scoreModelsByRoundIndex.first();
    return model;
}

QVector<const IDartsScoreModelsService::PlayerInput *> DartsScoreModelsService::dartsScoreModelsByTournamentIdAndHint(const QUuid &tournamentId, const int &hint) const
{
    auto dartsScoreInputs = _dartsInputsFilterService->filterByHint(_dartsScoresDb->models(),tournamentId,hint);
    return dartsScoreInputs;
}

void DartsScoreModelsService::addDartsScore(const IDartsScoreInput *scoreModel)
{
    _dartsScoresDb->addModel(scoreModel);
}

void DartsScoreModelsService::removeHiddenScores(const QUuid &tournamentId)
{
    auto dartsScoreInputs = _dartsInputsFilterService->filterByHint(_dartsScoresDb->models(),tournamentId,HiddenHint);
    _removeModelsService->service(dartsScoreInputs,_dartsScoresDb);
}

void DartsScoreModelsService::removeScoreById(const QUuid &scoreId)
{
    auto model = _getInputModelByIdService->service(scoreId,_dartsScoresDb);
    auto indexOfModel = _dartsScoresDb->indexOfModel(model);
    _dartsScoresDb->removeModelByIndex(indexOfModel);
}

void DartsScoreModelsService::removeScoresByTournamentId(const QUuid &tournamentId)
{
    auto tournamentScoreInputs = _dartsInputsFilterService->filterByTournamentId(_dartsScoresDb->models(),tournamentId);
    _removeModelsService->service(tournamentScoreInputs,_dartsScoresDb);
}

void DartsScoreModelsService::removeScoreModel(const QUuid &scoreId)
{
    auto model = _getInputModelByIdService->service(scoreId,_dartsScoresDb);
    auto indexOfModel = _dartsScoresDb->indexOfModel(model);
    _dartsScoresDb->removeModelByIndex(indexOfModel);
}

void DartsScoreModelsService::setDartsScoreHint(const PlayerInput *model, const int &hint)
{
    _setInputHintService->service(model,hint);
    _dartsScoresDb->saveState();
}

const IDartsScoreIndexes *DartsScoreModelsService::dartsScoreIndexes(const QUuid &tournamentId, const int &assignedPlayersCount) const
{
    auto dartsScoreInputs = _dartsInputsFilterService->filterByHint(_dartsScoresDb->models(),tournamentId,DisplayHint);
    auto orderedPlayerInputs = _sortDartsInputModelsByPredicate->service(dartsScoreInputs,_dartsScoreLessThanPredicate);
    auto indexes = _getDartsScoreIndexesByModels->buildIndexes(orderedPlayerInputs,assignedPlayersCount);
    return indexes;
}

int DartsScoreModelsService::dartsScoreCount(const QUuid &tournamentId, const int &hint) const
{
    auto dartsScoreInputs = _dartsInputsFilterService->filterByHint(_dartsScoresDb->models(),tournamentId,hint);
    return dartsScoreInputs.count();
}

DartsScoreModelsService *DartsScoreModelsService::setDartsInputsFilterService(FilterDartsInputsService *newDartsInputsFilterService)
{
    _dartsInputsFilterService = newDartsInputsFilterService;
    return this;
}

DartsScoreModelsService *DartsScoreModelsService::setRemoveModelsService(RemoveModelsService *newRemoveModelsService)
{
    _removeModelsService = newRemoveModelsService;
    return this;
}

DartsScoreModelsService *DartsScoreModelsService::setGetInputModelByIdService(GetDartsInputModelByIdService *newGetInputModelByIdService)
{
    _getInputModelByIdService = newGetInputModelByIdService;
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

DartsScoreModelsService *DartsScoreModelsService::setDbService(IDartsScoreDb *service)
{
    _dartsScoresDb = service;
    return this;
}
