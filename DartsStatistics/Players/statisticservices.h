#ifndef STATISTICSERVICES_H
#define STATISTICSERVICES_H
#include "Players/ijsontoplayer.h"
#include "Models/imirrorsdb.h"
#include "Db/istatsdb.h"
#include "ICreateStatModel.h"
class StatisticServices
{
public:
    typedef ICreateStatModel<CurrentStat> CreateStatistic;
    typedef IStatsDb<CurrentStat> DbContext;
    typedef IJsonToPlayer<CurrentStat> JsonToPlayer;
    JsonToPlayer *createPlayer() const {return _createPlayer;}
    void setCreateStatistics(JsonToPlayer *newCreatePlayer) {_createPlayer = newCreatePlayer;}
    DbContext *statModels() const {return _snapShots;}
    void setStatisticsDb(DbContext *newPlayersDb) {_snapShots = newPlayersDb;}
    CreateStatistic *createStatistic() const {return _createMirror;}
    void setCreateStatistic(CreateStatistic *newCreateMirror) {_createMirror = newCreateMirror;}
private:
    JsonToPlayer *_createPlayer;
    CreateStatistic *_createMirror;
    DbContext *_snapShots;
};
#endif // STATSSERVICES_H
