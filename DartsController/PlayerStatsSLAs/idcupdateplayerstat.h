#ifndef IDCUPDATEPLAYERSTAT_H
#define IDCUPDATEPLAYERSTAT_H
#include "idcstatscontext.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsController/DCInputSLAs/dciptvals.h"
class IDCUpdatePlayerStat
{
public:
    virtual void update(const DCIptVals &input, IDCStatsContext *playerStatsContext) const = 0;
    virtual void update(const QVector<DCIptVals> &inputs, IDCStatsContext *playerStatsContext) const = 0;
};
#endif // IDCUPDATEPLAYERSTAT_H
