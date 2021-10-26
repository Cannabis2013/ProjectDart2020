#ifndef DSCUPDATEMIDVAL_H
#define DSCUPDATEMIDVAL_H
#include "DartsController/PlayerStatsSLAs/idcupdatemidval.h"
class DSCUpdateMidVal : public IDCUpdateMidVal
{
public:
    virtual void update(DCInput &input, const DCIndex &index, IDCPlayerStats *playerStatsContext,
                        const IDCInitialScore *initialScore) const override
    {
        auto remainingScore = input.remainingScore;
        auto initial = initialScore->score();
        auto scoresAccumulated = initial - remainingScore;
        auto roundIndex = index.roundIndex;
        DCPlayerStat *playerStat;
        try {
            playerStat = &playerStatsContext->stat(input.playerId);
        }  catch (...)
        {
            return;
        }
        playerStat->middle = scoresAccumulated/roundIndex;
        input.middle = playerStat->middle;
    }
};
#endif // DSCCALCMIDDLEVAL_H
