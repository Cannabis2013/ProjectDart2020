#ifndef DCPLAYERSCORESSLAS_H
#define DCPLAYERSCORESSLAS_H

#include <qbytearray.h>
#include <qjsonobject.h>

#include <DartsController/Contracts/Models/dcplayer.h>

struct DCInput;
template<typename  T, typename U>class IDCPlayerManager;
template<typename  T> class IDCJsonToModels;
template<typename  T> class IDCJsonToModel;
template<typename  T> class IDCModelToJson;

class DCPlayersServices
{
public:
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCJsonToModels<DCPlayer> ByteArrayToPlayers;
    typedef IDCJsonToModel<DCPlayer> JsonToPlayer;
    typedef IDCModelToJson<DCPlayer> PlayerToJson;
    PlayerManager *playerManager() const {return _playerManager;}
    void setPlayerManager(PlayerManager *service) {_playerManager = service;}
    JsonToPlayer *jsonToPlayer() const {return _playerConverter;}
    void setPlayerConverter(JsonToPlayer *service) {_playerConverter = service;}
    ByteArrayToPlayers *jsonToPlayers() const {return _convertPlayers;}
    void setConvertPlayers(ByteArrayToPlayers *service) {_convertPlayers = service;}
    PlayerToJson *playerToJson() const {return _playerToJson;}
    void setPlayerToJson(PlayerToJson *newPlayerToJson) {_playerToJson = newPlayerToJson;}
private:
    ByteArrayToPlayers *_convertPlayers;
    JsonToPlayer *_playerConverter;
    PlayerManager *_playerManager;
    PlayerToJson *_playerToJson;
};
#endif // DSCSCORESERVICESPROVIDER_H
