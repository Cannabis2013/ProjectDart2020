#ifndef STATSSERVICES_H
#define STATSSERVICES_H
#include "Players/ijsontoplayer.h"
#include "Models/currentstats.h"
#include "Db/istatsdb.h"
namespace Statistics {
    class PlayerServices;
}
class CurrentStatsServices
{
public:
    typedef CurrentStats Stats;
    typedef IStatsDb<Stats> StatsDb;
    typedef IJsonToPlayer<Stats> JsonToPlayer;
    JsonToPlayer *createPlayer() const {return _createPlayer;}
    void setCreatePlayer(JsonToPlayer *newCreatePlayer) {_createPlayer = newCreatePlayer;}
    StatsDb *statsDb() const {return _playersDb;}
    void setPlayersDb(StatsDb *newPlayersDb) {_playersDb = newPlayersDb;}
private:
    JsonToPlayer *_createPlayer;
    StatsDb *_playersDb;
};
#endif // STATSSERVICES_H
