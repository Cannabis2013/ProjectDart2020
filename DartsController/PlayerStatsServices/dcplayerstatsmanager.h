#ifndef DCPLAYERSTATSMANAGER_H
#define DCPLAYERSTATSMANAGER_H
#include "DartsController/PlayerStatsSLAs/idcstatscontext.h"
#include <qregexp.h>
#include <math.h>
class DCPlayerStatsManager : public IDCStatsContext
{
public:
    virtual void setPlayers(const QStringList &names) override
    {
        for (const auto &name : names) {
            DCPlayerStat entity;
            entity.name = name;
            _playerStats << entity;
        }
    }
    DCPlayerStat &stat(const QString &name) override
    {
        for (auto &pStats : _playerStats) {
            if(pStats.name == name)
                return pStats;
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
