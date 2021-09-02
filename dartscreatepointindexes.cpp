#include "dartscreatepointindexes.h"
using namespace ModelsContext;

const IDartsPointIndexes *DartsCreatePointIndexes::createIndexes(const IModel<QUuid> *tournament,
                                                                 const IGetInputModelsService *getInputsService,
                                                                 const ISortInputModels *sortInputsService,
                                                                 const ICountInputModels *countInputsService,
                                                                 const IModelsDbContext *dbService) const
{
    auto models = getInputsService->inputModels(tournament->id(),DisplayHint,dbService);
    auto orderedModels = sortInputsService->sort(models,new SortDartsPointInputsByIndexes);
    auto totalInputModelsCount = countInputsService->count(tournament->id(),dbService);
    if(!orderedModels.isEmpty())
        return createDartsIndexesByModels(tournament,orderedModels,totalInputModelsCount);
    return createInitialDartsIndexes();
}

const IDartsPointIndexes *DartsCreatePointIndexes::createDartsIndexesByModels(const IModel<QUuid> *tournament,
                                                                              const QVector<const IModel<QUuid> *> &orderedModels,
                                                                              const int& totalInputModelsCount) const
{
    auto dartsTournament = dynamic_cast<const AbstractDartsTournament*>(tournament);
    auto playersCount = dartsTournament->assignedPlayerIds().count();
    auto indexes = DartsPointIndexes::createInstance();
    auto lastModel = dynamic_cast<const IDartsInput*>(orderedModels.last());
    auto totalTurns = totalInputModelsCount;
    auto turnIndex = orderedModels.count();
    auto roundIndex = lastModel->roundIndex();
    auto attemptIndex = lastModel->attempt();
    auto setIndex = lastModel->setIndex();
    if(++attemptIndex % dartsTournament->attempts() == 0)
    {
        attemptIndex = 0;
        setIndex++;
        if(setIndex >= playersCount)
        {
            roundIndex++;
            setIndex = 0;
        }
    }
    indexes->setTotalTurns(totalTurns);
    indexes->setTurnIndex(turnIndex);
    indexes->setRoundIndex(roundIndex);
    indexes->setSetIndex(setIndex);
    indexes->setAttemptIndex(attemptIndex);
    return indexes;
}

const IDartsPointIndexes *DartsCreatePointIndexes::createInitialDartsIndexes() const
{
    return DartsPointIndexes::createInitialInstance();
}

