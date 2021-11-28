#ifndef DCUPDATEPLAYERSTAT_H
#define DCUPDATEPLAYERSTAT_H
#include "DartsController/PlayerStatsSLAs/idcupdateplayerstat.h"
class DCUpdatePlayerStat : public IDCUpdatePlayerStat
{
public:
    virtual void update(const DCIptVals &input, IDCStatsContext *statsContext) const override
    {
        updatePlayerStat(input,&statsContext->stat(input.playerId));
    }
    virtual void update(const QVector<DCIptVals> &models, IDCStatsContext *playerStatsContext) const override
    {
        if(models.isEmpty())
            return;
        auto lastInput = models.last();
        auto lastPlayerId = lastInput.playerId;
        updatePlayerStat(lastInput,&playerStatsContext->stat(lastPlayerId));
        for (auto i = models.count() - 2; i >= 0; --i) {
            auto input = models.at(i);
            auto playerId = input.playerId;
            if(playerId != lastPlayerId)
            {
                updatePlayerStat(input,&playerStatsContext->stat(playerId));
                return;
            }
        }
    }
private:
    void updatePlayerStat(const DCIptVals &input, DCPlayerStat *stat) const
    {
        stat->min = input.min;
        stat->middle = input.mid;
        stat->max = input.max;
    }
};
#endif // DCUPDATEPLAYERSTAT_H
