#include "playermodelsjsondb.h"

using namespace DartsModelsContext;

void PlayerModelsJsonDb::fetchModels()
{
    try {
        _playerModels << _createPlayerModels->create(readJsonObjectFromFile(_fileName));
    } catch (...) {
        return;
    }
}

void PlayerModelsJsonDb::saveState()
{
    writeJsonObjectToFile(_createJsonFromModels->createJson(_playerModels),_fileName);
}

QVector<const IPlayerModel *> PlayerModelsJsonDb::models() const
{
    return _playerModels;
}

void PlayerModelsJsonDb::add(const IPlayerModel *player)
{
    _playerModels.append(player);
    saveState();
}

bool PlayerModelsJsonDb::remove(const int &index)
{
    _playerModels.remove(index);
    saveState();
    return true;
}

int PlayerModelsJsonDb::indexOf(const IPlayerModel *player) const
{
    auto index = _playerModels.indexOf(player);
    return index;
}

void PlayerModelsJsonDb::replace(const int &index, const IPlayerModel *player)
{
    _playerModels.replace(index,player);
    saveState();
}

const IPlayerModel *PlayerModelsJsonDb::model(const int &index) const
{
    auto count = _playerModels.count();
    if(index >= count)
        throw "Index out of range";
    auto model = _playerModels.at(index);
    return model;
}
