#ifndef DCSTATSCONTEXT_H
#define DCSTATSCONTEXT_H
#include "PlayerStatsSLAs/idcstatistics.h"
#include <qregexp.h>
#include <math.h>
#include "Models/dcstatsmodel.h"
#include <qstringlist.h>
#include "Models/dcinput.h"
#include "Models/dcplayer.h"
class DCStatsContext : public IDCStatistics
{
public:
    typedef QVector<DCInput> Inputs;
    virtual void setPlayers(const Players &players) override
    {
        _playerStats.clear();
        for (const auto &player : players) {
            DCStatsModel entity;
            entity.name = player.name;
            _playerStats << entity;
        }
    }
    DCStatsModel &stat(const QString &name) override
    {
        for (auto &pStats : _playerStats) {
            if(pStats.name == name)
                return pStats;
        }
        throw "PLAYERSTAT NOT FOUND";
    }
    QVector<DCStatsModel> &stats() override
    {
        return _playerStats;
    }
    void reset() override
    {
        for (auto &playerStat : _playerStats) {
            playerStat.max = -1;
            playerStat.middle = 0;
            playerStat.min = -1;
        }
    }
    void update(const DCInput &input) override
    {
        updatePlayerStat(input,&stat(input.playerName));
    }
    void update(const Inputs &inputs) override
    {
        if(inputs.isEmpty()) return;
        updatePlayerStats(getDistinctInputs(inputs));
    }
private:
    Inputs getDistinctInputs(const Inputs &inputs)
    {
        Inputs result;
        QString tempName;
        for (int i = inputs.count() - 1; i >= 0; --i) {
            auto input = inputs.at(i);
            auto name = input.playerName;
            if(name != tempName)
            {
                tempName = name;
                result << input;
            }
            auto playerIndex = input.playerIndex;
            if(playerIndex == 0)
                return result;
        }
        return result;
    }
    void updatePlayerStat(const DCInput &input, DCStatsModel *stat) const
    {
        stat->min = input.min;
        stat->middle = input.mid;
        stat->max = input.max;
    }
    void updatePlayerStats(const Inputs &inputs)
    {
        for (const auto &input : inputs)
            updatePlayerStat(input,&stat(input.playerName));
    }
    QVector<DCStatsModel> _playerStats;
};
#endif // DCRANGECALC_H
