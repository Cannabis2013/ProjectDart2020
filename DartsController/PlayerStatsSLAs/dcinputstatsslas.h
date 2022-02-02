#ifndef DCINPUTSTATSSLAS_H
#define DCINPUTSTATSSLAS_H
#include "idcupdatescorerange.h"
#include "idcstatistics.h"
class PlayerStatsSLAs
{
public:
    IDCStatistics *statisticsService() const {return _statsCtx;}
    void setStatistics(IDCStatistics *builder) {_statsCtx = builder;}
    IDCUpdateScoreRange *updateStatistics() const {return _setInputStats;}
    void setUpdateInputStats(IDCUpdateScoreRange *service) {_setInputStats = service;}
private:
    IDCUpdateScoreRange *_setInputStats;
    IDCStatistics *_statsCtx;
};
#endif // DCINPUTSTATSSLAS_H
