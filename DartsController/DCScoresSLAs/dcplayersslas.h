#ifndef DCPLAYERSCORESSLAS_H
#define DCPLAYERSCORESSLAS_H
#include "DCScoresSLAs/absdcplayersctx.h"
#include <qbytearray.h>
#include <qjsonobject.h>
#include "ModelBuilderSLAs/idcmodelconverter.h"
#include "ModelsConverterSLAs/idcmodelsconverter.h"
class DCPlayersSLAs
{
public:
    typedef AbsDCPlayersCtx<DCPlayer,DCInput> PlayerContext;
    PlayerContext *playerService() const {return _scoresModels;}
    void setPlayersContext(PlayerContext *service) {_scoresModels = service;}
    IDCModelConverter<DCPlayer> *playerConverter() const {return _playerConverter;}
    void setPlayerConverter(IDCModelConverter<DCPlayer> *service) {_playerConverter = service;}
    IDCModelsConverter<DCPlayer> *convertPlayers() const {return _convertPlayers;}
    void setConvertPlayers(IDCModelsConverter<DCPlayer> *service) {_convertPlayers = service;}
private:
    IDCModelsConverter<DCPlayer> *_convertPlayers;
    IDCModelConverter<DCPlayer> *_playerConverter;
    PlayerContext *_scoresModels;
};
#endif // DSCSCORESERVICESPROVIDER_H
