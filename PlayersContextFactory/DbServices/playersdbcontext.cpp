#include "playersdbcontext.h"
#include "DbSLAs/iplayer.h"
void PlayersDbContext::add(Model *player)
{
    _models.append(player);
}
PlayersDbContext::Model *PlayersDbContext::model(const int &index) const
{
    auto count = _models.count();
    if(index >= count)
        throw "Index out of range";
    auto model = _models.at(index);
    return model;
}
PlayersDbContext::Model *PlayersDbContext::model(std::function<bool (Model *)> predFunct) const
{
    for (const auto model : _models) {
        if(predFunct(model))
            return model;
    }
    return nullptr;
}
QVector<PlayersDbContext::Model *> PlayersDbContext::models() const
{
    return _models;
}
QVector<PlayersDbContext::Model *> PlayersDbContext::models(std::function<bool (Model *)> predFunct) const
{
    QVector<Model*> players;
    for (const auto &model : _models) {
        if(predFunct(model))
            players << model;
    }
    return players;
}
void PlayersDbContext::remove(const int &index)
{
    _models.remove(index);
}
void PlayersDbContext::remove(const QVector<int> &indexes)
{
    QVector<Model*> models;
    for (int i = 0; i < _models.count(); ++i) {
        if(!indexes.contains(i))
            models << _models.at(i);
    }
    _models = models;
}
int PlayersDbContext::indexOf(Model *player) const
{
    auto index = _models.indexOf(player);
    return index;
}
void PlayersDbContext::replace(const int &index, Model *player)
{
    _models.replace(index,player);
}
