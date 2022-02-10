#ifndef STATISTICSERVICES_H
#define STATISTICSERVICES_H
#include "Players/ijsontostatsmodel.h"
#include "Models/imirrorsdb.h"
#include "Db/istatsdb.h"
#include "ICreateStatModel.h"
class StatisticServices
{
public:
    typedef ICreateStatModel<CurrentStat> CreateStatistic;
    typedef IStatsDb<CurrentStat> DbContext;
    typedef IJsonToStatsModel<CurrentStat> JsonToStatsModel;
    JsonToStatsModel *jsonToStatsModel() const {return _createPlayer;}
    void setCreateStatistics(JsonToStatsModel *newCreatePlayer) {_createPlayer = newCreatePlayer;}
    DbContext *statModels() const {return _snapShots;}
    void setStatisticsDb(DbContext *newPlayersDb) {_snapShots = newPlayersDb;}
    CreateStatistic *createStatistic() const {return _createMirror;}
    void setCreateStatistic(CreateStatistic *newCreateMirror) {_createMirror = newCreateMirror;}
private:
    JsonToStatsModel *_createPlayer;
    CreateStatistic *_createMirror;
    DbContext *_snapShots;
};
#endif // STATSSERVICES_H
