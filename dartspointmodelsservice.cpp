#include "dartspointmodelsservice.h"

using namespace DartsModelsContext;

DartsModelsContext::DartsPointModelsService *DartsModelsContext::DartsPointModelsService::createInstance()
{
    return new DartsPointModelsService;
}

const DartsModelsContext::IDartsPointModelsService::PlayerInput *DartsModelsContext::DartsPointModelsService::dartsPointModel(const QUuid &tournamentId,
                                                                                                                              const QUuid &playerId,
                                                                                                                              const int &roundIndex,
                                                                                                                              const int &attemptIndex) const
{
    auto models = _dartsPointsDb->models();
    auto firstModel = _dartsInputsFilterService->filterByAttemptIndex(models,tournamentId,playerId,roundIndex,AllHints,attemptIndex);
    return firstModel;
}

DartsModelsContext::IDartsPointModelsService::PlayerInputs DartsModelsContext::DartsPointModelsService::dartsPointModelsByTournamentId(const QUuid &tournamentId) const
{
    auto dartsInputs = _dartsPointsDb->models();
    auto tournamentInputs = _dartsInputsFilterService->filterByTournamentId(dartsInputs,tournamentId);
    return tournamentInputs;
}

const DartsModelsContext::IDartsPointIndexes *DartsModelsContext::DartsPointModelsService::dartsPointIndexes(const QVector<const PlayerInput*>& models,
                                                                                                             const int& totalInputModelsCount,
                                                                                                             const int& assignedPlayersCount) const
{
    auto indexes = _assembleDartsPointIndexes->buildIndexes(models,assignedPlayersCount,totalInputModelsCount,models.count());
    return indexes;
}

void DartsModelsContext::DartsPointModelsService::addDartsPoint(const PlayerInput *model)
{
    _dartsPointsDb->addModel(model);
}

DartsModelsContext::IDartsPointModelsService::PlayerInputs DartsModelsContext::DartsPointModelsService::getDartsPointModelsOrdedByIndexes(const QUuid &tournamentId) const
{
    auto dartsInputs = _dartsPointsDb->models();
    auto tournamentInputs = _dartsInputsFilterService->filterByTournamentId(dartsInputs,tournamentId);
    auto orderedPlayerInputs = _sortDartsInputModelsByPredicate->service(tournamentInputs,_dartsPointLessThanPredicate);
    return orderedPlayerInputs;
}

const DartsModelsContext::IDartsPointModelsService::PlayerInput *DartsModelsContext::DartsPointModelsService::getDartsPointModelById(const QUuid &id) const
{
    auto pointModel = _getInputModelByIdService->service(id,_dartsPointsDb);
    return pointModel;
}

int DartsModelsContext::DartsPointModelsService::dartsPointsCount(const QUuid& tournamentId, const int& hint) const
{
    auto pointInputs = _dartsInputsFilterService->filterByHint(_dartsPointsDb->models(),tournamentId,hint);
    return pointInputs.count();
}

void DartsModelsContext::DartsPointModelsService::setDartsPointHint(const PlayerInput *inputModel, const int &hint)
{
    _setInputHintService->service(inputModel,hint);
    _dartsPointsDb->saveState();
}

void DartsModelsContext::DartsPointModelsService::removePointById(const QUuid& pointModelId)
{
    auto scoreModel = _getInputModelByIdService->service(pointModelId,_dartsPointsDb);
    auto index = _dartsPointsDb->indexOfModel(scoreModel);
    _dartsPointsDb->removeModelByIndex(index);
}

void DartsModelsContext::DartsPointModelsService::removeHiddenPoints(const QUuid& tournamentId)
{
    auto dartsPointInputs = _dartsInputsFilterService->filterByHint(_dartsPointsDb->models(),tournamentId,HiddenHint);
    _removeModelsService->service(dartsPointInputs,_dartsPointsDb);
}

void DartsModelsContext::DartsPointModelsService::removePointsByTournamentId(const QUuid& tournamentId)
{
    auto models = _dartsPointsDb->models();
    auto playerInputs = _dartsInputsFilterService->filterByTournamentId(models,tournamentId);
    _removeModelsService->service(playerInputs,_dartsPointsDb);
}

DartsPointModelsService *DartsPointModelsService::setDartsInputsFilterService(FilterDartsInputsService *newDartsInputsFilterService)
{
    _dartsInputsFilterService = newDartsInputsFilterService;
    return this;
}

DartsPointModelsService *DartsPointModelsService::setSortDartsInputModelsByPredicate(SortDartsInputsByPredicateService *newSortDartsInputModelsByPredicate)
{
    _sortDartsInputModelsByPredicate = newSortDartsInputModelsByPredicate;
    return this;
}

DartsPointModelsService *DartsPointModelsService::setAssembleDartsPointIndexes(IndexesBuilderService *newAssembleDartsPointIndexes)
{
    _assembleDartsPointIndexes = newAssembleDartsPointIndexes;
    return this;
}

DartsPointModelsService *DartsPointModelsService::setDartsSortingPredicate(IPredicate *newDartsPointLessThanPredicate)
{
    _dartsPointLessThanPredicate = newDartsPointLessThanPredicate;
    return this;
}

DartsPointModelsService *DartsPointModelsService::setDartsInputHintService(DartsInputHintService *newSetInputHintService)
{
    _setInputHintService = newSetInputHintService;
    return this;
}

DartsPointModelsService *DartsPointModelsService::setRemoveModelsService(RemoveModelsService *newRemoveModelsService)
{
    _removeModelsService = newRemoveModelsService;
    return this;
}

DartsPointModelsService *DartsPointModelsService::setGetInputModelByIdService(GetDartsInputModelByIdService *newGetInputModelByIdService)
{
    _getInputModelByIdService = newGetInputModelByIdService;
    return this;
}

DartsPointModelsService *DartsPointModelsService::setDbService(IDartsPointDb *newDartsPointsDb)
{
    _dartsPointsDb = newDartsPointsDb;
    return this;
}
QVector<const IDartsPointModelsService::PlayerInput *> DartsModelsContext::DartsPointModelsService::sortDartsPointsByIndexes(const PlayerInputs& models) const
{
    auto sortedModels = _sortDartsInputModelsByPredicate->service(models,_dartsPointLessThanPredicate);
    return sortedModels;
}
