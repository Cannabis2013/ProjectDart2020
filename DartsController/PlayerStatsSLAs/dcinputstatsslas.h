#ifndef DCINPUTSTATSSLAS_H
#define DCINPUTSTATSSLAS_H
#include "idcgetplayerstat.h"
#include "idcstatscontext.h"
#include "absdcsetiptstats.h"
class PlayerStatsSLAs
{
public:
    IDCStatsContext *statsContext() const {return _statsCtx;}
    void setStatsContext(IDCStatsContext *builder) {_statsCtx = builder;}
    IDCGetPlayerStat *getPlayerStat() const {return _getPlayerStat;}
    void setGetPlayerStat(IDCGetPlayerStat *newGetPlayerStat) {_getPlayerStat = newGetPlayerStat;}
    AbsDCSetIptStats *updateInputStats() const {return _setInputStats;}
    void setUpdateInputStats(AbsDCSetIptStats *service) {_setInputStats = service;}
private:
    AbsDCSetIptStats *_setInputStats;
    IDCGetPlayerStat *_getPlayerStat;
    IDCStatsContext *_statsCtx;
};
#endif // DCINPUTSTATSSLAS_H
