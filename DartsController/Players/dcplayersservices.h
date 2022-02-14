#ifndef DCPLAYERSCORESSLAS_H
#define DCPLAYERSCORESSLAS_H
#include "Players/idcplayermanager.h"
#include <qbytearray.h>
#include <qjsonobject.h>
#include "Converters/idcjsontomodel.h"
#include "Converters/idcjsontomodels.h"
#include "Converters/idcmodeltojson.h"

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
    PlayerToJson *playerToJson() const;
    void setPlayerToJson(PlayerToJson *newPlayerToJson);

private:
    ByteArrayToPlayers *_convertPlayers;
    JsonToPlayer *_playerConverter;
    PlayerManager *_playerManager;
    PlayerToJson *_playerToJson;
};

inline DCPlayersServices::PlayerToJson *DCPlayersServices::playerToJson() const
{
    return _playerToJson;
}

inline void DCPlayersServices::setPlayerToJson(DCPlayersServices::PlayerToJson *newPlayerToJson)
{
    _playerToJson = newPlayerToJson;
}
#endif // DSCSCORESERVICESPROVIDER_H
