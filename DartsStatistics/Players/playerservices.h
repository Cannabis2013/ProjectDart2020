#ifndef STATSSERVICES_H
#define STATSSERVICES_H
#include "Players/ijsontoplayer.h"
#include "Models/playerstat.h"
#include "Db/istatsdb.h"
namespace Statistics {
    class PlayerServices;
}
class PlayerServices
{
public:
    typedef PlayerStat Player;
    typedef IJsonToPlayer<Player> JsonToPlayer;
    typedef IStatsDb<Player> PlayersDb;
    JsonToPlayer *createPlayer() const {return _createPlayer;}
    void setCreatePlayer(JsonToPlayer *newCreatePlayer) {_createPlayer = newCreatePlayer;}
    PlayersDb *playersDb() const {return _playersDb;}
    void setPlayersDb(PlayersDb *newPlayersDb) {_playersDb = newPlayersDb;}
private:
    JsonToPlayer *_createPlayer;
    PlayersDb *_playersDb;
};
#endif // STATSSERVICES_H
