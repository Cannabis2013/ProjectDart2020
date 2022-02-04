#include "playersdb.h"
#include "Players/Models/playerstat.h"

void PlayersDb::add(const Model &model)
{
    _models.append(model);
}

PlayersDb::Model &PlayersDb::model(const int &index)
{
    return _models[index];
}

PlayersDb::Model &PlayersDb::model(Pred prefFunc)
{
    for (int i = 0; i < _models.count(); ++i) {
        auto m = _models[i];
        if(prefFunc(m))
            return _models[i];
    }
    throw "Model not found";
}

QVector<PlayersDb::Model> PlayersDb::models() const
{
    return _models;
}

QVector<PlayersDb::Model> PlayersDb::models(Pred prefFunc) const
{
    QVector<PlayerStat> players;

    for (const auto &player : _models) {
        if(prefFunc(player))
            players << player;
    }
    return players;
}

void PlayersDb::remove(const int &index)
{
    _models.remove(index);
}

void PlayersDb::remove(const QVector<int> &indexes)
{
    for (int i = indexes.count() - 1; i >= 0; --i) {
        auto index = indexes.at(i);
        _models.remove(index);
    }
}

void PlayersDb::clear()
{
    _models.clear();
}

int PlayersDb::indexOf(const Model &model) const
{
    for (int i = 0; i < _models.count(); ++i) {
        auto m = _models.at(i);
        if(m.name == model.name)
            return i;
    }
    return -1;
}

void PlayersDb::replace(const int &index, const Model &model)
{
    _models.replace(index,model);
}
