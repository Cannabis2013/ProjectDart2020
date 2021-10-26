#ifndef IDCGETPLAYERSTAT_H
#define IDCGETPLAYERSTAT_H
#include "dcplayerstat.h"
#include "idcplayerstats.h"
class IDCGetPlayerStat
{
public:
    virtual DCPlayerStat get(const QUuid &playerId, const IDCPlayerStats *playerStatsContext) const = 0;
};

#endif // IDCGETPLAYERSTAT_H
