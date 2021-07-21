#include "playermodelsservices.h"


IDartsPlayerModelBuilder *PlayerModelsServices::createPlayerModel() const
{
    return _createPlayerModel;
}

void PlayerModelsServices::setCreatePlayerModel(IDartsPlayerModelBuilder *newPlayerModelBuilder)
{
    _createPlayerModel = newPlayerModelBuilder;
}

IGetDataFromPlayerModels *PlayerModelsServices::getDataFromPlayerModels() const
{
    return _getDataFromPlayerModels;
}

void PlayerModelsServices::setGetDataFromPlayerModels(IGetDataFromPlayerModels *newGetDataFromPlayerModels)
{
    _getDataFromPlayerModels = newGetDataFromPlayerModels;
}

IDartsPlayerJsonBuilder *PlayerModelsServices::dartsPlayerCreateJson() const
{
    return _dartsPlayerJsonBuilder;
}

void PlayerModelsServices::setDartsPlayerJsonBuilder(IDartsPlayerJsonBuilder *newDartsPlayerJsonBuilder)
{
    _dartsPlayerJsonBuilder = newDartsPlayerJsonBuilder;
}

IDbService *PlayerModelsServices::dartsPlayersDb() const
{
    return _dartsPlayersDb;
}

void PlayerModelsServices::setDartsPlayersDb(IDbService *newDartsPlayersDb)
{
    _dartsPlayersDb = newDartsPlayersDb;
}

IGetDartsPlayerModelsFromDb *PlayerModelsServices::getPlayerModelsFromDb() const
{
    return _getPlayerModelsFromDb;
}

void PlayerModelsServices::setGetPlayerModelsFromDb(IGetDartsPlayerModelsFromDb *newGetDartsPlayerModelsFromDb)
{
    _getPlayerModelsFromDb = newGetDartsPlayerModelsFromDb;
}

ICreatePlayerModels *PlayerModelsServices::createPlayerModels() const
{
    return _createPlayerModels;
}

void PlayerModelsServices::setCreatePlayerModels(ICreatePlayerModels *newCreatePlayerModels)
{
    _createPlayerModels = newCreatePlayerModels;
}
