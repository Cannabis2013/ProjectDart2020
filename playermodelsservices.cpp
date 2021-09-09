#include "playermodelsservices.h"


ICreatePlayerFromJson *PlayerModelsServices::createPlayerModel() const
{
    return _createPlayerModel;
}

void PlayerModelsServices::setCreatePlayerModel(ICreatePlayerFromJson *newPlayerModelBuilder)
{
    _createPlayerModel = newPlayerModelBuilder;
}

ICreateJsonFromPlayers *PlayerModelsServices::dartsPlayerCreateJson() const
{
    return _jsonBuilder;
}

void PlayerModelsServices::setDartsPlayerJsonBuilder(ICreateJsonFromPlayers *newDartsPlayerJsonBuilder)
{
    _jsonBuilder = newDartsPlayerJsonBuilder;
}

IModelsDbContext *PlayerModelsServices::modelsDbContext() const
{
    return _dbContext;
}

void PlayerModelsServices::setModelsDbContext(IModelsDbContext *newDartsPlayersDb)
{
    _dbContext = newDartsPlayersDb;
}

IGetPlayersFromDb *PlayerModelsServices::getPlayerModelsFromDb() const
{
    return _getPlayerModelsFromDb;
}

void PlayerModelsServices::setGetPlayerModelsFromDb(IGetPlayersFromDb *newGetDartsPlayerModelsFromDb)
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

IRemoveModelsFromDb<IModelsDbContext> *PlayerModelsServices::removeFromDb() const
{
    return _removeFromDb;
}

void PlayerModelsServices::setRemoveFromDb(IRemoveModelsFromDb<IModelsDbContext> *newRemoveFromDb)
{
    _removeFromDb = newRemoveFromDb;
}
