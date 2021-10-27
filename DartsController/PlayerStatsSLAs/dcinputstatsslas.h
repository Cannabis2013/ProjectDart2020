#ifndef DCINPUTSTATSSLAS_H
#define DCINPUTSTATSSLAS_H
#include "idcupdatemidval.h"
#include "idcgetplayerstat.h"
#include "idcplayerstats.h"
#include "idcupdateplayerstat.h"
#include "idcupdatescorerange.h"
class PlayerStatsSLAs
{
public:
    IDCPlayerStats *playerStats() const
    {
        return _statsBuilder;
    }
    void setPlayerStatsManager(IDCPlayerStats *builder)
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
    IDCUpdateMidVal *calcMidVal() const
    {
        return _updateMidVal;
    }
    void setUpdateMiddleVal(IDCUpdateMidVal *newCalcMiddleVal)
    {
        _updateMidVal = newCalcMiddleVal;
    }
    IDCUpdateScoreRange *updateScoreRange() const
    {
        return _updateScoreRange;
    }
    void setUpdateScoreRange(IDCUpdateScoreRange *service)
    {
        _updateScoreRange = service;
    }
private:
    IDCUpdateMidVal *_updateMidVal;
    IDCUpdateScoreRange *_updateScoreRange;
    IDCGetPlayerStat *_getPlayerStat;
    IDCUpdatePlayerStat *_updatePlayerStats;
    IDCPlayerStats *_statsBuilder;
};
#endif // DCINPUTSTATSSLAS_H
