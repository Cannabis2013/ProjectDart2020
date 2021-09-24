#ifndef DMCCREATEINDEXES_H
#define DMCCREATEINDEXES_H

#include "DartsModelsContext/DMCIndexesSLAs/idartscreateindexes.h"
#include "DartsModelsContext/DMCIndexesServices/dartsindexes.h"
#include "DartsModelsContext/DMCTournamentSLAs/abstractdartstournament.h"
#include "sortdartspointinputsbyindexes.h"

class DMCCreateIndexes : public IDartsCreateIndexes<IDartsIndexes>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    virtual const IDartsIndexes *createIndexes(const IModel<QUuid> *tournament,
                                                    const IGetInputModelsService *getInputsService,
                                                    const ISortInputModels *sortInputsService,
                                                    const ICountInputModels *countInputsService,
                                                    const IModelsDbContext *dbService) const override
    {
        auto models = getInputsService->inputModels(tournament->id(),DisplayHint,dbService);
        auto orderedModels = sortInputsService->sort(models,new SortDartsPointInputsByIndexes);
        auto totalInputModelsCount = countInputsService->count(tournament->id(),dbService);
        if(!orderedModels.isEmpty())
            return createDartsIndexesByModels(tournament,orderedModels,totalInputModelsCount);
        return createInitialDartsIndexes();
    }
private:
    const IDartsIndexes* createDartsIndexesByModels(const IModel<QUuid> *tournament, const QVector<const IModel<QUuid> *> &orderedModels, const int &totalInputModelsCount) const
    {
        auto dartsTournament = dynamic_cast<const AbstractDartsTournament*>(tournament);
        auto playersCount = dartsTournament->assignedPlayerIds().count();
        auto indexes = ModelsContext::DartsIndexes::createInstance();
        auto lastModel = dynamic_cast<const ModelsContext::IDartsInput*>(orderedModels.last());
        auto totalTurns = totalInputModelsCount;
        auto turnIndex = orderedModels.count();
        auto roundIndex = lastModel->roundIndex();
        auto attemptIndex = lastModel->attempt();
        auto setIndex = lastModel->setIndex();
        if(++attemptIndex % 3 == 0)
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
    };
    const IDartsIndexes* createInitialDartsIndexes() const
    {
        return ModelsContext::DartsIndexes::createInitialInstance();
    }
};

#endif // GETLASTENTEREDDARTSPOINTMODEL_H
