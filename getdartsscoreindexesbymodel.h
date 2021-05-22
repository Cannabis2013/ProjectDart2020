#ifndef ASSEMBLEDARTSSCOREINDEXESBYMODEL_H
#define ASSEMBLEDARTSSCOREINDEXESBYMODEL_H

#include "iternaryservice.h"
#include "idartspointinput.h"
#include "idartsmodelsservice.h"
#include <quuid.h>
#include "dartsscoreindexes.h"

class GetDartsScoreIndexesByModel : public
        ITernaryService<const QVector<const IDartsScoreInput*>&,
                       const IDartsTournament*,
                       const int&,
                       const IDartsScoreIndexes*>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    const IDartsScoreIndexes* service(const QVector<const IDartsScoreInput*>& orderedModels,
                                      const IDartsTournament* model,
                                      const int& dartsTournamentPointsCount) override
    {
        if(!orderedModels.isEmpty())
            return assembleDartsIndexesByModels(orderedModels,model,dartsTournamentPointsCount);
        return assembleInitialDartsIndexes();
    }
private:
    const IDartsScoreIndexes* assembleDartsIndexesByModels(const QVector<const IDartsScoreInput*>& orderedModels,
                                                          const IDartsTournament* model,
                                                          const int& dartsTournamentPointsCount)
    {
        auto indexes = DartsScoreIndexes::createInstance();
        auto lastModel = orderedModels.last();
        auto assignedPlayerIds = model->assignedPlayerIdentities();
        auto playersCount = assignedPlayerIds.count();
        auto totalTurns = orderedModels.count();
        auto turnIndex = dartsTournamentPointsCount;
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
    };
    const IDartsScoreIndexes* assembleInitialDartsIndexes()
    {
        return DartsScoreIndexes::createInitialInstance();
    }
};


#endif // ASSEMBLEDARTSSCOREINDEXESBYMODEL_H
