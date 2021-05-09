#ifndef GETLASTENTEREDDARTSPOINTMODEL_H
#define GETLASTENTEREDDARTSPOINTMODEL_H

#include "iternaryservice.h"
#include "idartspointinput.h"
#include "idartsmodelsservice.h"
#include <quuid.h>
#include "dartspointindexes.h"

class AssembleDartsPointIndexesByDartsPointModel : public
        ITernaryService<const QVector<const IDartsPointInput*>&,
                       const IDartsTournament*,
                       const int&,
                       const IDartsPointIndexes*>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    const IDartsPointIndexes* service(const QVector<const IDartsPointInput*>& orderedModels,
                                      const IDartsTournament* model,
                                      const int& dartsTournamentPointsCount) override
    {
        if(!orderedModels.isEmpty())
            return assembleDartsIndexesByModels(orderedModels,model,dartsTournamentPointsCount);
        return assembleInitialDartsIndexes();
    }
private:
    const IDartsPointIndexes* assembleDartsIndexesByModels(const QVector<const IDartsPointInput*>& orderedModels,
                                                          const IDartsTournament* model,
                                                          const int& dartsTournamentPointsCount)
    {
        auto indexes = DartsPointIndexes::createInstance();
        auto lastModel = orderedModels.last();
        auto assignedPlayerIds = model->assignedPlayerIdentities();
        auto playersCount = assignedPlayerIds.count();
        auto attempts = model->attempts();
        auto totalTurns = orderedModels.count();
        auto turnIndex = dartsTournamentPointsCount;
        auto roundIndex = lastModel->roundIndex();
        auto attemptIndex = lastModel->attempt();
        auto setIndex = lastModel->setIndex();
        if(++attemptIndex % attempts == 0)
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
    const IDartsPointIndexes* assembleInitialDartsIndexes()
    {
        return DartsPointIndexes::createInitialInstance();
    }
};

#endif // GETLASTENTEREDDARTSPOINTMODEL_H
