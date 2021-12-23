#ifndef IDCGETPLAYERSTAT_H
#define IDCGETPLAYERSTAT_H
class IDCStatsContext;
struct DCPlayerStats;
class QUuid;
class IDCGetPlayerStat
{
public:
    virtual DCPlayerStats get(const QUuid &playerId, const IDCStatsContext *playerStatsContext) const = 0;
};

#endif // IDCGETPLAYERSTAT_H
