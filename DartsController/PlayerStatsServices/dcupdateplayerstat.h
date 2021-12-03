#ifndef DCUPDATEPLAYERSTAT_H
#define DCUPDATEPLAYERSTAT_H
#include "DartsController/PlayerStatsSLAs/idcupdateplayerstat.h"
class DCUpdatePlayerStat : public IDCUpdatePlayerStat
{
public:
    virtual void update(const DCIptVals &input, IDCStatsContext *statsContext) const override
    {
        updatePlayerStat(input,&statsContext->stat(input.playerName));
    }
    virtual void update(const QVector<DCIptVals> &models, IDCStatsContext *playerStatsContext) const override
    {
        if(models.isEmpty())
            return;
        auto lastInput = models.last();
        auto lastPlayerName = lastInput.playerName;
        updatePlayerStat(lastInput,&playerStatsContext->stat(lastPlayerName));
        for (auto i = models.count() - 2; i >= 0; --i) {
            auto input = models.at(i);
            auto playerName = input.playerName;
            if(playerName != lastPlayerName)
            {
                updatePlayerStat(input,&playerStatsContext->stat(playerName));
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
