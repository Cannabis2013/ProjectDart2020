#ifndef DCPLAYERSCORESSLAS_H
#define DCPLAYERSCORESSLAS_H
#include "DCScoresSLAs/absdcplayersctx.h"
#include "DCScoresSLAs/absdccreatescore.h"
#include "idcupdateplayerstats.h"
#include <qbytearray.h>
#include <qjsonobject.h>
#include "ModelBuilderSLAs/idcmodelbuilder.h"
#include "ModelsConverterSLAs/idcmodelsconverter.h"
class DCPlayersSLAs
{
public:
    AbsDCPlayersCtx *playersContext() const {return _scoresModels;}
    void setPlayersContext(AbsDCPlayersCtx *service) {_scoresModels = service;}
    AbsDCCreateScore *scoreCalc() const {return _calculateScore;}
    void setGetScoreFromInput(AbsDCCreateScore *service) {_calculateScore = service;}
    IDCUpdatePlayerStats *updatePlayerDetails() const {return _updateScores;}
    void setUpdateScores(IDCUpdatePlayerStats *service) {_updateScores = service;}
    IDCModelBuilder<DCPlayer, QJsonObject> *playerConverter() const {return _playerConverter;}
    void setPlayerConverter(IDCModelBuilder<DCPlayer, QJsonObject> *service) {_playerConverter = service;}
    IDCModelsConverter<DCPlayer, QJsonObject> *convertPlayers() const {return _convertPlayers;}
    void setConvertPlayers(IDCModelsConverter<DCPlayer, QJsonObject> *service) {_convertPlayers = service;}
private:
    IDCModelsConverter<DCPlayer,QJsonObject> *_convertPlayers;
    IDCModelBuilder<DCPlayer,QJsonObject> *_playerConverter;
    AbsDCPlayersCtx *_scoresModels;
    AbsDCCreateScore *_calculateScore;
    IDCUpdatePlayerStats *_updateScores;
};
#endif // DSCSCORESERVICESPROVIDER_H
