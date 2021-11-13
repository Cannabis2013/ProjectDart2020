#ifndef DCUPDATEPLAYERSTAT_H
#define DCUPDATEPLAYERSTAT_H
#include "DartsController/PlayerStatsSLAs/idcupdateplayerstat.h"
class DCUpdatePlayerStat : public IDCUpdatePlayerStat
{
public:
    virtual void update(const AbstractDartsInput *input, IDCPlayerStats *playerStatsContext) const override
    {
        updatePlayerStat(input,&playerStatsContext->stat(input->playerId()));
    }
    virtual void update(const QVector<AbstractDartsInput*> &inputs, IDCPlayerStats *playerStatsContext) const override
    {
        if(inputs.isEmpty())
            return;
        auto lastInput = inputs.last();
        auto lastPlayerId = lastInput->playerId();
        updatePlayerStat(lastInput,&playerStatsContext->stat(lastPlayerId));
        for (auto i = inputs.count() - 2; i >= 0; --i) {
            auto input = inputs.at(i);
            auto playerId = input->playerId();
            if(playerId != lastPlayerId)
            {
                updatePlayerStat(input,&playerStatsContext->stat(playerId));
                return;
            }
        }
    }
private:
    void updatePlayerStat(const AbstractDartsInput *input, DCPlayerStat *stat) const
    {
        stat->min = input->currentMinimum();
        stat->middle = input->middleValue();
        stat->max = input->currentMaximum();
    }

};
#endif // DCUPDATEPLAYERSTAT_H
