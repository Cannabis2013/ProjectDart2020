#include "playermodelsservices.h"


IDartsPlayerModelBuilder *PlayerModelsServices::playerModelBuilder() const
{
    return _playerModelBuilder;
}

void PlayerModelsServices::setPlayerModelBuilder(IDartsPlayerModelBuilder *newPlayerModelBuilder)
{
    _playerModelBuilder = newPlayerModelBuilder;
}

IGetDataFromPlayerModels *PlayerModelsServices::getDataFromPlayerModels() const
{
    return _getDataFromPlayerModels;
}

void PlayerModelsServices::setGetDataFromPlayerModels(IGetDataFromPlayerModels *newGetDataFromPlayerModels)
{
    _getDataFromPlayerModels = newGetDataFromPlayerModels;
}

IDartsPlayerJsonBuilder *PlayerModelsServices::dartsPlayerJsonBuilder() const
{
    return _dartsPlayerJsonBuilder;
}

void PlayerModelsServices::setDartsPlayerJsonBuilder(IDartsPlayerJsonBuilder *newDartsPlayerJsonBuilder)
{
    _dartsPlayerJsonBuilder = newDartsPlayerJsonBuilder;
}

IDartsPlayerDbManipulator *PlayerModelsServices::playerDbManipulator() const
{
    return _playerDbManipulator;
}

void PlayerModelsServices::setPlayerDbManipulator(IDartsPlayerDbManipulator *newPlayerDbManipulator)
{
    _playerDbManipulator = newPlayerDbManipulator;
}

IPlayerModelsDb *PlayerModelsServices::dartsPlayersDb() const
{
    return _dartsPlayersDb;
}

void PlayerModelsServices::setDartsPlayersDb(IPlayerModelsDb *newDartsPlayersDb)
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
