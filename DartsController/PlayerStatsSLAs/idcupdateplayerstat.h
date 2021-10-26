#ifndef IDCUPDATEPLAYERSTAT_H
#define IDCUPDATEPLAYERSTAT_H
#include "idcplayerstats.h"
class IDCUpdatePlayerStat
{
public:
    virtual void update(DCInput &input, IDCPlayerStats *playerStatsContext) const = 0;
    virtual void update(const QVector<DCInput> &inputs, IDCPlayerStats *playerStatsContext) const = 0;
};
#endif // IDCUPDATEPLAYERSTAT_H
