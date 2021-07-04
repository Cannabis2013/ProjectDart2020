#include "dartspointmodelsservice.h"

using namespace DartsModelsContext;

DartsModelsContext::DartsPointModelsService *DartsModelsContext::DartsPointModelsService::createInstance()
{
    return new DartsPointModelsService;
}

const DartsPointModelsService::PlayerInput *DartsModelsContext::DartsPointModelsService::dartsPointModel(const QUuid &tournamentId,
                                                                                                         const QUuid &playerId,
                                                                                                         const int &roundIndex,
                                                                                                         const int &attemptIndex,
                                                                                                         const IDartsInputDb* dbService) const
{
    auto models = dbService->models();
    auto firstModel = _dartsInputsFilterService->filterByAttemptIndex(models,tournamentId,playerId,roundIndex,AllHints,attemptIndex);
    return firstModel;
}

const DartsModelsContext::IDartsPointIndexes *DartsModelsContext::DartsPointModelsService::dartsPointIndexes(const QVector<const PlayerInput*>& models,
                                                                                                             const int& totalInputModelsCount,
                                                                                                             const int& assignedPlayersCount) const
{
    auto indexes = _assembleDartsPointIndexes->buildIndexes(models,assignedPlayersCount,totalInputModelsCount,models.count());
    return indexes;
}

void DartsModelsContext::DartsPointModelsService::setDartsPointHint(const PlayerInput *inputModel,
                                                                    const int &hint,
                                                                    IDartsInputDb* dbService)
{
    _setInputHintService->service(inputModel,hint);
    dbService->saveState();
}

DartsPointModelsService *DartsPointModelsService::setDartsInputsFilterService(FilterDartsInputsService *newDartsInputsFilterService)
{
    _dartsInputsFilterService = newDartsInputsFilterService;
    return this;
}

DartsPointModelsService *DartsPointModelsService::setAssembleDartsPointIndexes(IndexesBuilderService *newAssembleDartsPointIndexes)
{
    _assembleDartsPointIndexes = newAssembleDartsPointIndexes;
    return this;
}

DartsPointModelsService *DartsPointModelsService::setDartsInputHintService(DartsInputHintService *newSetInputHintService)
{
    _setInputHintService = newSetInputHintService;
    return this;
}
