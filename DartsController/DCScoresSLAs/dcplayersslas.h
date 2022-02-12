#ifndef DCPLAYERSCORESSLAS_H
#define DCPLAYERSCORESSLAS_H
#include "DCScoresSLAs/idcplayermanager.h"
#include <qbytearray.h>
#include <qjsonobject.h>
#include "ModelBuilderSLAs/idcmodelconverter.h"
#include "ModelsConverterSLAs/idcmodelsconverter.h"
class DCPlayersSLAs
{
public:
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    PlayerManager *playerManager() const {return _playerManager;}
    void setPlayerManager(PlayerManager *service) {_playerManager = service;}
    IDCModelConverter<DCPlayer> *playerConverter() const {return _playerConverter;}
    void setPlayerConverter(IDCModelConverter<DCPlayer> *service) {_playerConverter = service;}
    IDCModelsConverter<DCPlayer> *convertPlayers() const {return _convertPlayers;}
    void setConvertPlayers(IDCModelsConverter<DCPlayer> *service) {_convertPlayers = service;}
private:
    IDCModelsConverter<DCPlayer> *_convertPlayers;
    IDCModelConverter<DCPlayer> *_playerConverter;
    PlayerManager *_playerManager;
};
#endif // DSCSCORESERVICESPROVIDER_H
