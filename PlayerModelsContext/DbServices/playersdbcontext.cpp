#include "playersdbcontext.h"

#include "AsyncUtils/runnable.h"

PlayersDbContext::PlayersDbContext(FileReaderInterface *fileReader, FileWriteInterface *fileWriter)
{
    fileReader->setFileName(_fileName);
    fileWriter->setFileName(_fileName);
    setReadJsonFromFile(fileReader);
    setWriteJsonToFile(fileWriter);
}

bool PlayersDbContext::fetchModels(const IPlayerContextModelBuilder *modelBuilder)
{
    auto future = readJson()->read();
    Runnable::runLater([=]{
        _playerModels = modelBuilder->createPlayers(future.result());
    },future);
    return true;
}

QFuture<bool> PlayersDbContext::saveChanges(const IPlayerJsonBuilder *jsonBuilder)
{
    return saveJson()->save(jsonBuilder->toJson(_playerModels));
}

QVector<IModel<QUuid> *> PlayersDbContext::models() const
{
    return _playerModels;
}

PlayersDbContext *PlayersDbContext::add(IModel<QUuid> *player)
{
    _playerModels.append(player);
    return this;
}

PlayersDbContext *PlayersDbContext::remove(const int &index)
{
    _playerModels.remove(index);
    return this;
}

IPlayersDbContext *PlayersDbContext::remove(const QVector<int> &indexes)
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _playerModels.count(); ++i) {
        if(!indexes.contains(i))
            models << _playerModels.at(i);
    }
    _playerModels = models;
    return this;
}

int PlayersDbContext::indexOf(IModel<QUuid> *player) const
{
    auto index = _playerModels.indexOf(player);
    return index;
}

PlayersDbContext *PlayersDbContext::replace(const int &index, IModel<QUuid> *player)
{
    _playerModels.replace(index,player);
    return this;
}

IModel<QUuid> *PlayersDbContext::model(const int &index) const
{
    auto count = _playerModels.count();
    if(index >= count)
        throw "Index out of range";
    auto model = _playerModels.at(index);
    return model;
}
