#ifndef IDCUPDATEPLAYERSTAT_H
#define IDCUPDATEPLAYERSTAT_H
#include "idcplayerstats.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class IDCUpdatePlayerStat
{
public:
    virtual void update(const AbstractDartsInput *input, IDCPlayerStats *playerStatsContext) const = 0;
    virtual void update(const QVector<IModel<QUuid>*> &inputs, IDCPlayerStats *playerStatsContext) const = 0;
};
#endif // IDCUPDATEPLAYERSTAT_H
