#ifndef IDCGETPLAYERSTAT_H
#define IDCGETPLAYERSTAT_H
#include "dcplayerstat.h"
#include "idcstatscontext.h"
class IDCGetPlayerStat
{
public:
    virtual DCPlayerStat get(const QUuid &playerId, const IDCStatsContext *playerStatsContext) const = 0;
};

#endif // IDCGETPLAYERSTAT_H
