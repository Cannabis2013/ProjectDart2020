#include "playersjsondb.h"

void PlayersJsonDb::fetchModels()
{
    QJsonObject jsonObject;
    try {
        jsonObject = readJSONFromFile(_fileName);
    } catch (...) {
        return;
    }
    auto playersJson = jsonObject["Players"].toArray();
    _playerModels << _playerJsonExtractorService->service(playersJson);
}

void PlayersJsonDb::saveState()
{
    QJsonObject modelJSON;
    modelJSON["Players"] = _playerModelsAssemblerService->assembleJsonArrayFromModels(playerModels());
    writeJSONToFile(modelJSON,"Models");
}

QVector<const IModel<QUuid>*> PlayersJsonDb::playerModels()
{
    return _playerModels;
}

void PlayersJsonDb::addPlayerModel(const IModel<QUuid> *player)
{
    _playerModels.append(player);
    saveState();
}

void PlayersJsonDb::removePlayerModel(const QUuid &id)
{
    for (const auto& playerInterface : qAsConst(_playerModels)) {
        if(playerInterface->id() == id)
        {
            _playerModels.removeOne(playerInterface);
            return;
        }
    }
}

void PlayersJsonDb::removePlayerModel(const int &index)
{
    _playerModels.remove(index);
    saveState();
}

int PlayersJsonDb::indexOfPlayerModel(const IModel<QUuid> *player)
{
    auto index = _playerModels.indexOf(player);
    return index;
}

void PlayersJsonDb::replacePlayerModel(const int &index, const IModel<QUuid> *player)
{
    _playerModels.replace(index,player);
    saveState();
}

const IModel<QUuid>* PlayersJsonDb::playerModel(const int &index)
{
    auto count = _playerModels.count();
    if(index >= count)
        throw "Index out of range";
    auto model = _playerModels.at(index);
    return model;
}
