#ifndef STATISTICSERVICES_H
#define STATISTICSERVICES_H

#include "Models/currentstats.h"
#include "ICreateStatModel.h"
#include <DartsStatistics/Contracts/Db/istatsdb.h>

class StatisticServices
{
public:
    typedef ICreateStatModel<CurrentStat> CreateStatistic;
    typedef IStatsDb<CurrentStat> DbContext;
    DbContext *statModels() const {return _snapShots;}
    void setStatisticsDb(DbContext *newPlayersDb) {_snapShots = newPlayersDb;}
    CreateStatistic *createStatistic() const {return _createStatsModel;}
    void setCreateStatistic(CreateStatistic *newCreateMirror) {_createStatsModel = newCreateMirror;}
private:
    CreateStatistic *_createStatsModel;
    DbContext *_snapShots;
};
#endif // STATSSERVICES_H
