#ifndef DCUPDPLASTATS_H
#define DCUPDPLASTATS_H
#include "DCScoresSLAs/absdcupdscoresdetails.h"
#include "DCScoresSLAs/absdcplayersctx.h"
class DCUpdatePlayerStats : public AbsDCUpdScoresDetails
{
public:
    DCUpdatePlayerStats(IDCStatsContext *statsCtx, AbsDCPlayersCtx  *playersCtx):
    AbsDCUpdScoresDetails(statsCtx,playersCtx){}
    virtual void update(const DCInput &ipt) override
    {
        statsCtx()->update(ipt);
        scoresCtx()->updateScore(ipt);
    }
};

#endif // DCUPDPLASTATS_H
