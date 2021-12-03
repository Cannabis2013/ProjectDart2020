#ifndef DCINPUTSTATSSLAS_H
#define DCINPUTSTATSSLAS_H
#include "idccalcmidval.h"
#include "idcgetplayerstat.h"
#include "idcstatscontext.h"
#include "idcupdateplayerstat.h"
#include "idcsetinputstats.h"
class PlayerStatsSLAs
{
public:
    IDCStatsContext *statsContext() const
    {
        return _statsBuilder;
    }
    void setPlayerStatsManager(IDCStatsContext *builder)
    {
        _statsBuilder = builder;
    }
    IDCUpdatePlayerStat *updatePlayerStats() const
    {
        return _updatePlayerStats;
    }
    void setUpdatePlayerStats(IDCUpdatePlayerStat *newUpdatePlayerStats)
    {
        _updatePlayerStats = newUpdatePlayerStats;
    }
    IDCGetPlayerStat *getPlayerStat() const
    {
        return _getPlayerStat;
    }
    void setGetPlayerStat(IDCGetPlayerStat *newGetPlayerStat)
    {
        _getPlayerStat = newGetPlayerStat;
    }
    IDCCalcMidVal *calcMidVal() const
    {
        return _updateMidVal;
    }
    void setUpdateMiddleVal(IDCCalcMidVal *newCalcMiddleVal)
    {
        _updateMidVal = newCalcMiddleVal;
    }
    IDCSetInputStats *setInputStats() const
    {
        return _setInputStats;
    }
    void setUpdateScoreRange(IDCSetInputStats *service)
    {
        _setInputStats = service;
    }
private:
    IDCCalcMidVal *_updateMidVal;
    IDCSetInputStats *_setInputStats;
    IDCGetPlayerStat *_getPlayerStat;
    IDCUpdatePlayerStat *_updatePlayerStats;
    IDCStatsContext *_statsBuilder;
};
#endif // DCINPUTSTATSSLAS_H
