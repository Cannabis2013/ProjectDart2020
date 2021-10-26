#ifndef DCUPDATEPLAYERSTAT_H
#define DCUPDATEPLAYERSTAT_H
#include "DartsController/PlayerStatsSLAs/idcupdateplayerstat.h"
class DCUpdatePlayerStat : public IDCUpdatePlayerStat
{
public:
    virtual void update(DCInput &input, IDCPlayerStats *playerStatsContext) const override
    {
        updatePlayerStat(input,&playerStatsContext->stat(input.playerId));
    }
    virtual void update(const QVector<DCInput> &inputs, IDCPlayerStats *playerStatsContext) const override
    {
        if(inputs.isEmpty())
            return;
        auto lastInput = inputs.last();
        auto lastPlayerId = lastInput.playerId;
        updatePlayerStat(lastInput,&playerStatsContext->stat(lastPlayerId));
        for (auto i = inputs.count() - 2; i >= 0; --i) {
            auto input = inputs.at(i);
            auto playerId = input.playerId;
            if(playerId != lastPlayerId)
            {
                updatePlayerStat(input,&playerStatsContext->stat(playerId));
                return;
            }
        }
    }
private:
    void updatePlayerStat(DCInput &input, DCPlayerStat *stat) const
    {
        stat->min = input.min;
        stat->middle = input.middle;
        stat->max = input.max;
    }

};
#endif // DCUPDATEPLAYERSTAT_H
