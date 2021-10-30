#ifndef DCUPDATESCORERANGE_H
#define DCUPDATESCORERANGE_H
#include "DartsController/PlayerStatsSLAs/idcsetinputstats.h"
class DCUpdateScoreRange : public IDCSetInputStats
{
public:
    virtual void set(DCInput &input, IDCPlayerStats *statsService, const IDCCalcMidVal *calcMidVal, const DCIndex &index, const int &initialScore) const override
    {
        DCPlayerStat *playerStat;
        try {
            playerStat = &statsService->stat(input.playerId);
        }  catch (...)
        {
            return;
        }
        evaulateAndUpdateStats(playerStat,input.score);
        setInputRangeStats(input,playerStat);
        input.middle = calcMidVal->middleValue(index,input.remainingScore,initialScore);
    }
private:
    void evaulateAndUpdateStats(DCPlayerStat *playerStat, const int &score) const
    {
        if(playerStat->min > score || playerStat->min == -1)
            playerStat->min = score;
        if(playerStat->max < score)
            playerStat->max = score;
    }
    void setInputRangeStats(DCInput &input, DCPlayerStat *playerStat) const
    {
        input.min = playerStat->min;
        input.max = playerStat->max;
    }

};
#endif // DCUPDATESCORERANGE_H
