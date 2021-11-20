#ifndef DCPLAYERSTATSMANAGER_H
#define DCPLAYERSTATSMANAGER_H
#include "DartsController/PlayerStatsSLAs/idcstatscontext.h"
#include <qregexp.h>
#include <math.h>
class DCPlayerStatsManager : public IDCStatsContext
{
public:
    virtual void setPlayers(const Players &players) override
    {
        for (const auto &player : players) {
            DCPlayerStat entity;
            entity.playerId = player->id();
            _playerStats << entity;
        }
    }
    DCPlayerStat &stat(const QUuid &playerId) override
    {
        for (auto &playerStat : _playerStats) {
            if(playerStat.playerId == playerId)
                return playerStat;
        }
        throw "PLAYERSTAT NOT FOUND";
    }
    virtual QVector<DCPlayerStat> &stats() override
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
private:
    QVector<DCPlayerStat> _playerStats;
};
#endif // DCRANGECALC_H
