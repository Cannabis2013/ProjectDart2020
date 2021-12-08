#ifndef PLAYERSDBCONTEXT_H
#define PLAYERSDBCONTEXT_H
#include <quuid.h>
#include "PlayerModelsContext/DbSLAs/IPlayersDbContext.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "PlayerModelsContext/Services/playermodel.h"
class PlayersDbContext : public IPlayersDbContext
{
public:
    void add(IModel<QUuid> *player) override {_models.append(player);}
    IModel<QUuid> *model(const int &index) const override
    {
        auto count = _models.count();
        if(index >= count)
            throw "Index out of range";
        auto model = _models.at(index);
        return model;
    }
    IModel<QUuid>* model(std::function<bool (IModel<QUuid>*)> predFunct) const override
    {
        for (const auto model : _models) {
            if(predFunct(model))
                return model;
        }
        return nullptr;
    }
    QVector<IModel<QUuid>*> models() const override {return _models;}
    QVector<IModel<QUuid>*> models(std::function<bool(IModel<QUuid>*)> predFunct) const override
    {
        QVector<IModel<QUuid>*> players;
        for (const auto &model : _models) {
            if(predFunct(model))
                players << model;
        }
        return players;
    }
    void remove(const int &index) override {_models.remove(index);}
    void remove(const QVector<int> &indexes) override
    {
        QVector<IModel<QUuid>*> models;
        for (int i = 0; i < _models.count(); ++i) {
            if(!indexes.contains(i))
                models << _models.at(i);
        }
        _models = models;
    }
    int indexOf(IModel<QUuid> *player) const override
    {
        auto index = _models.indexOf(player);
        return index;
    }
    void replace(const int &index, IModel<QUuid> *player) override {_models.replace(index,player);}
private:
    QVector<IModel<QUuid>*> _models;
};
#endif // LOCALTOURNAMENTMODELDB_H
