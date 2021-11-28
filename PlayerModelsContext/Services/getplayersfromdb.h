#ifndef GETPLAYERSFROMDB_H
#define GETPLAYERSFROMDB_H
#include "PlayerModelsContext/DbSLAs/igetplayerfromdb.h"
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
class GetPlayersFromDb : public IGetPlayersFromDb
{
public:
    virtual Player *player(const QUuid &id, const IModelsDbContext *dbContext) const override
    {
        auto players = dbContext->models();
        return model(id,players);
    }
    Player *player(const QString &name, const IModelsDbContext *dbContext) const override
    {
        auto model = dbContext->model([name](IModel<QUuid>* m){
                auto player = dynamic_cast<IPlayerModel*>(m);
                if(player->name() == name)
                    return true;
                return false;
            });
        return dynamic_cast<IPlayerModel*>(model);
    }
    QVector<IPlayerModel*> players(const QVector<int> &indexes, const IModelsDbContext *dbContext) const override
    {
        auto models = dbContext->models();
        QVector<IPlayerModel*> playerModels;
        for (const auto &index : indexes)
            playerModels << model(index,models);
        return playerModels;
    }
    Players players(const QVector<QUuid> &ids, const IModelsDbContext *dbContext) const override
    {
        auto models = dbContext->models([ids](IModel<QUuid>* m){
                auto player = dynamic_cast<IPlayerModel*>(m);
                return ids.contains(player->name());
            });
        return convert(models);
    }
    Players players(const QVector<QString> &names, const IModelsDbContext *dbContext) const override
    {
        auto models = dbContext->models([names](IModel<QUuid>* m){
                auto player = dynamic_cast<IPlayerModel*>(m);
                return names.contains(player->name());
            });
        return convert(models);
    }
private:
    IPlayerModel *model(const int &index, const QVector<IModel<QUuid> *> &models) const
    {
        if(index < 0 || index >= models.count())
            return nullptr;
        return dynamic_cast<IPlayerModel*>(models.at(index));
    }
    IPlayerModel *model(const QUuid &id, const QVector<IModel<QUuid> *> &models) const
    {
        for (auto &model : models)
        {
            if(model->id() == id)
                return dynamic_cast<IPlayerModel*>(model);
        }
        return nullptr;
    }
    Players convert(const QVector<IModel<QUuid>*> &models) const
    {
        Players list;
        for (const auto &model : models)
            list << dynamic_cast<IPlayerModel*>(model);
        return list;
    }
};
#endif // GETPLAYERDATAFROMDB_H
