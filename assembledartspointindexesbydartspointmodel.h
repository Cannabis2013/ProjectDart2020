#ifndef GETLASTENTEREDDARTSPOINTMODEL_H
#define GETLASTENTEREDDARTSPOINTMODEL_H

#include "iternaryservice.h"
#include "idartspointinput.h"
#include "idartsmodelsservice.h"
#include <quuid.h>
#include "dartspointindexes.h"

class AssembleDartsPointIndexesByDartsPointModel : public
        ITernaryService<const QVector<const IDartsPointInput<QUuid>*>&,
                        const QUuid&,
                        const IDartsModelsService*,
                        const IDartsPointIndexes*>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    const IDartsPointIndexes* service(const QVector<const IDartsPointInput<QUuid>*>& orderedModels,
                                      const QUuid& tournamentId,
                                      const IDartsModelsService* modelsService) override
    {
        auto lastModel = orderedModels.last();
        auto assignedPlayerIds = modelsService->tournamentAssignedPlayers(tournamentId);
        auto playersCount = assignedPlayerIds.count();
        auto attempts = modelsService->tournamentAttempts(tournamentId);
        auto totalTurns = orderedModels.count();
        auto turnIndex = modelsService->dartsPointsCount(ModelDisplayHint::DisplayHint);
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
        auto indexes = new DartsPointIndexes;
        indexes->setTotalTurns(totalTurns);
        indexes->setTurnIndex(turnIndex);
        indexes->setRoundIndex(roundIndex);
        indexes->setSetIndex(setIndex);
        indexes->setAttemptIndex(attemptIndex);
        return indexes;
    }
};

#endif // GETLASTENTEREDDARTSPOINTMODEL_H
