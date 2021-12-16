#ifndef PLAYERSDBCONTEXT_H
#define PLAYERSDBCONTEXT_H
#include <qvector.h>
#include "PlayerModelsContext/DbSLAs/IPlayersDbContext.h"
#include "PlayerModelsContext/Services/playermodel.h"
class PlayersDbContext : public IPlayersDbContext<IPlayer>
{
public:
    void add(Model *player) override {_models.append(player);}
    Model *model(const int &index) const override
    {
        auto count = _models.count();
        if(index >= count)
            throw "Index out of range";
        auto model = _models.at(index);
        return model;
    }
    Model* model(std::function<bool (Model*)> predFunct) const override
    {
        for (const auto model : _models) {
            if(predFunct(model))
                return model;
        }
        return nullptr;
    }
    QVector<Model*> models() const override {return _models;}
    QVector<Model*> models(std::function<bool(Model*)> predFunct) const override
    {
        QVector<Model*> players;
        for (const auto &model : _models) {
            if(predFunct(model))
                players << model;
        }
        return players;
    }
    void remove(const int &index) override {_models.remove(index);}
    void remove(const QVector<int> &indexes) override
    {
        QVector<Model*> models;
        for (int i = 0; i < _models.count(); ++i) {
            if(!indexes.contains(i))
                models << _models.at(i);
        }
        _models = models;
    }
    int indexOf(Model *player) const override
    {
        auto index = _models.indexOf(player);
        return index;
    }
    void replace(const int &index, Model *player) override {_models.replace(index,player);}
private:
    QVector<Model*> _models;
};
#endif // LOCALTOURNAMENTMODELDB_H
