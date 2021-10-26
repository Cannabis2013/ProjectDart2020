#ifndef DCUPDATESCORERANGE_H
#define DCUPDATESCORERANGE_H
#include "DartsController/PlayerStatsSLAs/idcupdatescorerange.h"
class DCUpdateScoreRange : public IDCUpdateScoreRange
{
public:
    virtual void update(DCInput &input, IDCPlayerStats *playerStatsContext) const override
    {
        DCPlayerStat *playerStat;
        try {
            playerStat = &playerStatsContext->stat(input.playerId);
        }  catch (...)
        {
            return;
        }
        initializeStat(playerStat,input.score);
        setInputValues(input,playerStat);
    }
private:
    void initializeStat(DCPlayerStat *playerStat, const int &score) const
    {
        if(playerStat->min > score || playerStat->min == -1)
            playerStat->min = score;
        if(playerStat->max < score)
            playerStat->max = score;
    }
    void setInputValues(DCInput &input, DCPlayerStat *playerStat) const
    {
        input.min = playerStat->min;
        input.max = playerStat->max;
    }
};
#endif // DCUPDATESCORERANGE_H
