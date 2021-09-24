#include "playermodelsslas.h"


ICreatePlayerFromJson *PlayerModelsSLAs::createPlayerModel() const
{
    return _createPlayerModel;
}

void PlayerModelsSLAs::setCreatePlayerModel(ICreatePlayerFromJson *newPlayerModelBuilder)
{
    _createPlayerModel = newPlayerModelBuilder;
}

ICreateJsonFromPlayers *PlayerModelsSLAs::dartsPlayerCreateJson() const
{
    return _jsonBuilder;
}

void PlayerModelsSLAs::setDartsPlayerJsonBuilder(ICreateJsonFromPlayers *newDartsPlayerJsonBuilder)
{
    _jsonBuilder = newDartsPlayerJsonBuilder;
}

IModelsDbContext *PlayerModelsSLAs::modelsDbContext() const
{
    return _dbContext;
}

void PlayerModelsSLAs::setModelsDbContext(IModelsDbContext *newDartsPlayersDb)
{
    _dbContext = newDartsPlayersDb;
}

IGetPlayersFromDb *PlayerModelsSLAs::getPlayerModelsFromDb() const
{
    return _getPlayerModelsFromDb;
}

void PlayerModelsSLAs::setGetPlayerModelsFromDb(IGetPlayersFromDb *newGetDartsPlayerModelsFromDb)
{
    _getPlayerModelsFromDb = newGetDartsPlayerModelsFromDb;
}

ICreatePlayerModels *PlayerModelsSLAs::createPlayerModels() const
{
    return _createPlayerModels;
}

void PlayerModelsSLAs::setCreatePlayerModels(ICreatePlayerModels *newCreatePlayerModels)
{
    _createPlayerModels = newCreatePlayerModels;
}

IRemoveModelsFromDb<IModelsDbContext> *PlayerModelsSLAs::removeFromDb() const
{
    return _removeFromDb;
}

void PlayerModelsSLAs::setRemoveFromDb(IRemoveModelsFromDb<IModelsDbContext> *newRemoveFromDb)
{
    _removeFromDb = newRemoveFromDb;
}
