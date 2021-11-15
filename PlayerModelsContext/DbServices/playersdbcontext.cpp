#include "playersdbcontext.h"

#include "AsyncUtils/runlater.h"

PlayersDbContext::PlayersDbContext(FileReaderInterface *fileReader, FileWriteInterface *fileWriter)
{
    fileReader->setFileName(_fileName);
    fileWriter->setFileName(_fileName);
    setReadJsonFromFile(fileReader);
    setWriteJsonToFile(fileWriter);
}

bool PlayersDbContext::fetch(const IPlayerContextModelBuilder *modelBuilder)
{
    auto future = readJson()->read();
    RunLater::run([=]{
        _models = modelBuilder->createPlayers(future.result());
    },future);
    return true;
}

QFuture<bool> PlayersDbContext::saveChanges(const IPlayerJsonBuilder *jsonBuilder)
{
    return saveJson()->saveAsync(jsonBuilder->toJson(_models));
}

QVector<IModel<QUuid> *> PlayersDbContext::models() const
{
    return _models;
}

QVector<IModel<QUuid>*> PlayersDbContext::models(std::function<bool(IModel<QUuid>*)> predFunct) const
{
    QVector<IModel<QUuid>*> players;
    for (const auto &model : _models) {
        if(predFunct(model))
            players << model;
    }
    return players;
}

PlayersDbContext *PlayersDbContext::add(IModel<QUuid> *player)
{
    _models.append(player);
    return this;
}

PlayersDbContext *PlayersDbContext::remove(const int &index)
{
    _models.remove(index);
    return this;
}

IPlayersDbContext *PlayersDbContext::remove(const QVector<int> &indexes)
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _models.count(); ++i) {
        if(!indexes.contains(i))
            models << _models.at(i);
    }
    _models = models;
    return this;
}

int PlayersDbContext::indexOf(IModel<QUuid> *player) const
{
    auto index = _models.indexOf(player);
    return index;
}

PlayersDbContext *PlayersDbContext::replace(const int &index, IModel<QUuid> *player)
{
    _models.replace(index,player);
    return this;
}

IModel<QUuid> *PlayersDbContext::model(const int &index) const
{
    auto count = _models.count();
    if(index >= count)
        throw "Index out of range";
    auto model = _models.at(index);
    return model;
}

IModel<QUuid> *PlayersDbContext::model(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    for (const auto model : _models) {
        if(predFunct(model))
            return model;
    }
    return nullptr;
}
