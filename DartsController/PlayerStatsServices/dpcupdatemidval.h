#ifndef DPCUPDATEMIDVAL_H
#define DPCUPDATEMIDVAL_H
#include "DartsController/PlayerStatsSLAs/idcupdatemidval.h"
class DPCUpdateMidVal : public IDCUpdateMidVal
{
public:
    virtual void update(DCInput &input, const DCIndex &index, IDCPlayerStats *playerStatsContext,const IDCInitialScore *initialScore) const override
    {
        auto remainingScore = input.remainingScore;
        auto initial = initialScore->score();
        auto scoresAccumulated = initial - remainingScore;
        auto divisor = index.roundIndex*3 + index.attemptIndex - 2;
        DCPlayerStat *playerStat;
        try {
            playerStat = &playerStatsContext->stat(input.playerId);
        }  catch (...)
        {
            return;
        }
        playerStat->middle = scoresAccumulated/divisor;
        input.middle = playerStat->middle;
    }
};

#endif // DPCUPDATEMIDVAL_H
