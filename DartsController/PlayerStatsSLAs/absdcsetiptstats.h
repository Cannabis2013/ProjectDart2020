#ifndef ABSDCSETIPTSTATS_H
#define ABSDCSETIPTSTATS_H
#include "DartsController/PlayerStatsServices/dcstatscontext.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsController/DCInputSLAs/dcinput.h"
class AbsDCSetIptStats
{
public:
    AbsDCSetIptStats(IDCStatsContext *statsCtx):
        _statsContext(statsCtx){}
    virtual void set(DCInput &input, const DCIndex &idx, const int &initRemScore) const = 0;
    IDCStatsContext *statsContext() const {return _statsContext;}
private:
    IDCStatsContext *_statsContext;
};
#endif // IDCDETSCORERANGE_H
