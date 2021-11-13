#ifndef DCUPDATESCORERANGE_H
#define DCUPDATESCORERANGE_H
#include "DartsController/PlayerStatsSLAs/idcsetinputstats.h"
class DCUpdateScoreRange : public IDCSetInputStats
{
public:
    virtual void set(AbstractDartsInput *input, IDCPlayerStats *statsService, const IDCCalcMidVal *calcMidVal, IDartsIndex *index, const int &initialScore) const override
    {
        DCPlayerStat *playerStat;
        try {
            playerStat = &statsService->stat(input->playerId());
        }  catch (...)
        {
            return;
        }
        evaulateAndUpdateStats(playerStat,input->score());
        setInputRangeStats(input,playerStat);
        input->setMiddleValue(calcMidVal->middleValue(index,input->remainingScore(),initialScore));
    }
private:
    void evaulateAndUpdateStats(DCPlayerStat *playerStat, const int &score) const
    {
        if(playerStat->min > score || playerStat->min == -1)
            playerStat->min = score;
        if(playerStat->max < score)
            playerStat->max = score;
    }
    void setInputRangeStats(AbstractDartsInput *input, DCPlayerStat *playerStat) const
    {
        input->setCurrentMinimum(playerStat->min);
        input->setCurrentMaximum(playerStat->max);
    }
};
#endif // DCUPDATESCORERANGE_H
