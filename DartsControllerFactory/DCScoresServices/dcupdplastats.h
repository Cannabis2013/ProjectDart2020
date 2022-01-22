#ifndef DCUPDPLASTATS_H
#define DCUPDPLASTATS_H
#include "DCScoresSLAs/idcupdateplayerstats.h"
#include "DCScoresSLAs/absdcplayersctx.h"
#include "PlayerStatsSLAs/idcstatistics.h"
class DCUpdatePlayerStats : public IDCUpdatePlayerStats
{
public:
    void update(const DCInput &ipt, IDCStatistics *statsCtx, AbsDCPlayersCtx  *playersCtx) override
    {
        statsCtx->update(ipt);
        playersCtx->updateScore(ipt);
    }
};

#endif // DCUPDPLASTATS_H
