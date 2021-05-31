#ifndef ASSEMBLEDARTSSCOREINDEXESBYMODEL_H
#define ASSEMBLEDARTSSCOREINDEXESBYMODEL_H

#include "iternaryservice.h"
#include "idartspointinput.h"
#include "idartsmodelsservice.h"
#include <quuid.h>
#include "dartsscoreindexes.h"
#include "idartsmultiattemptindexesbuilder.h"

class GetDartsScoreIndexesByModel : public
        IDartsMultiAttemptIndexesBuilder<IDartsScoreIndexes,IDartsInput>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    const IDartsScoreIndexes* buildIndexes(const QVector<const IDartsInput*>& orderedModels,
                                           const int& assignedPlayersCount) const override
    {
        if(!orderedModels.isEmpty())
            return assembleDartsIndexesByModels(orderedModels,assignedPlayersCount);
        return assembleInitialDartsIndexes();
    }
private:
    const IDartsScoreIndexes* assembleDartsIndexesByModels(const QVector<const IDartsInput*>& orderedModels,
                                                           const int& assignedPlayersCount) const
    {
        auto indexes = DartsScoreIndexes::createInstance();
        auto lastModel = dynamic_cast<const IDartsScoreInput*>(orderedModels.last());
        auto totalTurns = orderedModels.count();
        auto turnIndex = orderedModels.count();
        auto roundIndex = lastModel->roundIndex();
        auto setIndex = lastModel->setIndex();
        if(++setIndex >= assignedPlayersCount)
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
    const IDartsScoreIndexes* assembleInitialDartsIndexes() const
    {
        return DartsScoreIndexes::createInitialInstance();
    }
};


#endif // ASSEMBLEDARTSSCOREINDEXESBYMODEL_H
