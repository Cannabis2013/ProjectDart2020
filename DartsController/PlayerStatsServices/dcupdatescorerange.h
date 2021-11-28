#ifndef DCUPDATESCORERANGE_H
#define DCUPDATESCORERANGE_H
#include "DartsController/PlayerStatsSLAs/idcsetinputstats.h"
class DCUpdateScoreRange : public IDCSetInputStats
{
public:
    DCUpdateScoreRange(IDCStatsContext *statsContext, IDCCalcMidVal *calcMidVal,
                       AbstractDCIdxCtrl *indexCtrl, IDCMetaCtx *metaContext)
    {
        setStatsContext(statsContext);
        setCalcMidVal(calcMidVal);
        setIndexCtrl(indexCtrl);
        setMetaContext(metaContext);
    }
    virtual void set(DCIptVals &input) const override
    {
        DCPlayerStat *playerStat;
        try {
            playerStat = &statsContext()->stat(input.playerId);
        }  catch (...)
        {
            return;
        }
        evaulateAndUpdateStats(playerStat,input.score);
        setInputRangeStats(input,playerStat);
        auto initialRemaining = metaContext()->get().initialRemainingScore;
        input.mid = calcMidVal()->middleValue(indexCtrl()->index(),input.remainingScore,initialRemaining);
    }
private:
    void evaulateAndUpdateStats(DCPlayerStat *playerStat, const int &score) const
    {
        if(playerStat->min > score || playerStat->min == -1)
            playerStat->min = score;
        if(playerStat->max < score)
            playerStat->max = score;
    }
    void setInputRangeStats(DCIptVals &input, DCPlayerStat *playerStat) const
    {
        input.min = playerStat->min;
        input.max = playerStat->max;
    }
};
#endif // DCUPDATESCORERANGE_H
