#ifndef DCPLAYERSCORESSLAS_H
#define DCPLAYERSCORESSLAS_H
#include "DCScoresSLAs/idcplayermanager.h"
#include <qbytearray.h>
#include <qjsonobject.h>
#include "ModelBuilderSLAs/idcjsontomodel.h"
#include "ModelsConverterSLAs/idcjsontomodels.h"
class DCPlayersServices
{
public:
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCJsonToModels<DCPlayer> ConvertPlayers;
    typedef IDCJsonToModel<DCPlayer> ConvertPlayer;
    PlayerManager *playerManager() const {return _playerManager;}
    void setPlayerManager(PlayerManager *service) {_playerManager = service;}
    ConvertPlayer *jsonToPlayer() const {return _playerConverter;}
    void setPlayerConverter(ConvertPlayer *service) {_playerConverter = service;}
    ConvertPlayers *jsonToPlayers() const {return _convertPlayers;}
    void setConvertPlayers(ConvertPlayers *service) {_convertPlayers = service;}
private:
    ConvertPlayers *_convertPlayers;
    ConvertPlayer *_playerConverter;
    PlayerManager *_playerManager;
};
#endif // DSCSCORESERVICESPROVIDER_H
