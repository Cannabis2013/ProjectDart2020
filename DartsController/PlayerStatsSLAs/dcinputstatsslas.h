#ifndef DCINPUTSTATSSLAS_H
#define DCINPUTSTATSSLAS_H
#include "idcsetiptstats.h"
#include "idcstatistics.h"
class PlayerStatsSLAs
{
public:
    IDCStatistics *statisticsService() const {return _statsCtx;}
    void setStatistics(IDCStatistics *builder) {_statsCtx = builder;}
    IDCSetIptStats *updateStatistics() const {return _setInputStats;}
    void setUpdateInputStats(IDCSetIptStats *service) {_setInputStats = service;}
private:
    IDCSetIptStats *_setInputStats;
    IDCStatistics *_statsCtx;
};
#endif // DCINPUTSTATSSLAS_H
