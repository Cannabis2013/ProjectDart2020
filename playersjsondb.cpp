#include "playersjsondb.h"

PlayersJsonDb *PlayersJsonDb::createInstance(PlayersJsonDb::JsonExtractor*jsonExtractorService,
                                             PlayersJsonDb::JsonAssembler* jsonAssemblerService)
{
    auto db = (new PlayersJsonDb())
            ->setPlayerJsonExtractorService(jsonExtractorService)
            ->setPlayerModelsAssemblerService(jsonAssemblerService);
    db->fetchModels();
    return db;
}

void PlayersJsonDb::fetchModels()
{
    QJsonObject jsonObject;
    try {
        jsonObject = readJsonObjectFromFile(_fileName);
    } catch (...) {
        return;
    }
    auto playersJson = jsonObject["Players"].toArray();
    _playerModels << _playerJsonExtractorService->service(playersJson);
}

void PlayersJsonDb::saveState()
{
    QJsonObject modelJSON;
    modelJSON["Players"] = _playerModelsAssemblerService->service(playerModels());
    writeJsonObjectToFile(modelJSON,_fileName);
}

QVector<const IPlayerModel *> PlayersJsonDb::playerModels()
{
    return _playerModels;
}

void PlayersJsonDb::addPlayerModel(const IPlayerModel *player)
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

int PlayersJsonDb::indexOfPlayerModel(const IPlayerModel *player)
{
    auto index = _playerModels.indexOf(player);
    return index;
}

void PlayersJsonDb::replacePlayerModel(const int &index, const IPlayerModel *player)
{
    _playerModels.replace(index,player);
    saveState();
}

PlayersJsonDb* PlayersJsonDb::setPlayerModelsAssemblerService(IUnaryService<const QVector<const IPlayerModel *> &, QJsonArray> *playerModelsAssemblerService)
{
    _playerModelsAssemblerService = playerModelsAssemblerService;
    return this;
}

PlayersJsonDb* PlayersJsonDb::setPlayerJsonExtractorService(IUnaryService<const QJsonArray &, QVector<const IPlayerModel *> > *playerJsonExtractorService)
{
    _playerJsonExtractorService = playerJsonExtractorService;
    return this;
}
const IPlayerModel *PlayersJsonDb::playerModel(const int &index)
{
    auto count = _playerModels.count();
    if(index >= count)
        throw "Index out of range";
    auto model = _playerModels.at(index);
    return model;
}
