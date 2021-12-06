#ifndef DCSTATSCONTEXT_H
#define DCSTATSCONTEXT_H
#include "DartsController/PlayerStatsSLAs/idcstatscontext.h"
#include <qregexp.h>
#include <math.h>
class DCStatsContext : public IDCStatsContext
{
public:
    virtual void setPlayers(const QStringList &names) override
    {
        _playerStats.clear();
        for (const auto &name : names) {
            DCPlayerStats entity;
            entity.name = name;
            _playerStats << entity;
        }
    }
    DCPlayerStats &stat(const QString &name) override
    {
        for (auto &pStats : _playerStats) {
            if(pStats.name == name)
                return pStats;
        }
        throw "PLAYERSTAT NOT FOUND";
    }
    virtual QVector<DCPlayerStats> &stats() override
    {
        return _playerStats;
    }
    virtual void reset() override
    {
        for (auto &playerStat : _playerStats) {
            playerStat.max = -1;
            playerStat.middle = 0;
            playerStat.min = -1;
        }
    }
    virtual void update(const DCInput &input) override
    {
        updatePlayerStat(input,&stat(input.playerName));
    }
    virtual void update(const QVector<DCInput> &inputs) override
    {
        if(inputs.isEmpty()) return;
        auto lastInput = inputs.last();
        auto lastPlayerName = lastInput.playerName;
        updatePlayerStat(lastInput,&stat(lastPlayerName));
        for (auto i = inputs.count() - 2; i >= 0; --i) {
            auto input = inputs.at(i);
            auto playerName = input.playerName;
            if(playerName != lastPlayerName)
            {
                updatePlayerStat(input,&stat(playerName));
                return;
            }
        }
    }
private:
    void updatePlayerStat(const DCInput &input, DCPlayerStats *stat) const
    {
        stat->min = input.min;
        stat->middle = input.mid;
        stat->max = input.max;
    }
    QVector<DCPlayerStats> _playerStats;
};
#endif // DCRANGECALC_H
