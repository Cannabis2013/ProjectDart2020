#ifndef IDCGETPLAYERSTAT_H
#define IDCGETPLAYERSTAT_H
#include "dcplayerstats.h"
#include "idcstatscontext.h"
class IDCGetPlayerStat
{
public:
    virtual DCPlayerStats get(const QUuid &playerId, const IDCStatsContext *playerStatsContext) const = 0;
};

#endif // IDCGETPLAYERSTAT_H
