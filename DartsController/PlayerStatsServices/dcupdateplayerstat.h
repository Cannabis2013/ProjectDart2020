#ifndef DCUPDATEPLAYERSTAT_H
#define DCUPDATEPLAYERSTAT_H
#include "DartsController/PlayerStatsSLAs/idcupdateplayerstat.h"
class DCUpdatePlayerStat : public IDCUpdatePlayerStat
{
public:
    virtual void update(const AbstractDartsInput *input, IDCStatsContext *playerStatsContext) const override
    {
        updatePlayerStat(input,&playerStatsContext->stat(input->playerId()));
    }
    virtual void update(const QVector<IModel<QUuid>*> &models, IDCStatsContext *playerStatsContext) const override
    {
        if(models.isEmpty())
            return;
        auto lastInput = dynamic_cast<AbstractDartsInput*>(models.last());
        auto lastPlayerId = lastInput->playerId();
        updatePlayerStat(lastInput,&playerStatsContext->stat(lastPlayerId));
        for (auto i = models.count() - 2; i >= 0; --i) {
            auto model = models.at(i);
            auto input = dynamic_cast<AbstractDartsInput*>(model);
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
