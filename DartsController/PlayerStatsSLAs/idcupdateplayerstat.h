#ifndef IDCUPDATEPLAYERSTAT_H
#define IDCUPDATEPLAYERSTAT_H
#include "idcstatscontext.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class IDCUpdatePlayerStat
{
public:
    virtual void update(const AbstractDartsInput *input, IDCStatsContext *playerStatsContext) const = 0;
    virtual void update(const QVector<IModel<QUuid>*> &inputs, IDCStatsContext *playerStatsContext) const = 0;
};
#endif // IDCUPDATEPLAYERSTAT_H
