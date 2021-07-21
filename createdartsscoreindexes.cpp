#include "createdartsscoreindexes.h"

using namespace ModelsContext;

const IDartsScoreIndexes *ModelsContext::CreateDartsScoreIndexes::createIndexes(const IModel<QUuid> *tournament,
                                                                                const IGetInputModelsService *getInputsService,
                                                                                const ISortInputModels *sortInputsService,
                                                                                const ICountInputModels *countInputsService,
                                                                                const IDbService *dbService) const
{
    auto models = getInputsService->inputModels(tournament->id(),DisplayHint,dbService);
    auto orderedModels = sortInputsService->sort(models,new SortDartsScoreInputsByIndexes);
    auto totalModelsCount = countInputsService->count(tournament->id(),dbService);
    if(!orderedModels.isEmpty())
        return createDartsIndexesByModels(tournament,orderedModels, totalModelsCount);
    return createInitialDartsIndexes();
}

const IDartsScoreIndexes *CreateDartsScoreIndexes::createDartsIndexesByModels(const IModel<QUuid> *tournament,
                                                                              const QVector<const IModel<QUuid> *> &orderedModels,
                                                                              const int &totalModelsCount) const
{
    auto dartsTournament = dynamic_cast<const IDartsTournament*>(tournament);
    auto playersCount = dartsTournament->assignedPlayerIds().count();
    auto indexes = DartsScoreIndexes::createInstance();
    auto lastModel = dynamic_cast<const IDartsScoreInput*>(orderedModels.last());
    auto totalTurns = totalModelsCount;;
    auto turnIndex = orderedModels.count();
    auto roundIndex = lastModel->roundIndex();
    auto setIndex = lastModel->setIndex();
    if(++setIndex >= playersCount)
    {
        roundIndex++;
        setIndex = 0;
    }
    indexes->setTotalTurns(totalTurns);
    indexes->setTurnIndex(turnIndex);
    indexes->setRoundIndex(roundIndex);
    indexes->setSetIndex(setIndex);
    return indexes;
}

const IDartsScoreIndexes *CreateDartsScoreIndexes::createInitialDartsIndexes() const
{
    return DartsScoreIndexes::createInitialInstance();
}
