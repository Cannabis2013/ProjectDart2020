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
        return dbContext->model([name](IModel<QUuid>* m){
            auto player = dynamic_cast<IPlayerModel*>(m);
            if(player->name() == name)
                return true;
            return false;
        });
    }
    QVector<IModel<QUuid> *> players(const QVector<int> &indexes, const IModelsDbContext *dbContext) const override
    {
        auto models = dbContext->models();
        QVector<IModel<QUuid>*> playerModels;
        for (const auto &index : indexes)
            playerModels << model(index,models);
        return playerModels;
    }
    Players players(const QVector<QUuid> &ids, const IModelsDbContext *dbContext) const override
    {
        return dbContext->models([ids](IModel<QUuid>* m){
                auto player = dynamic_cast<IPlayerModel*>(m);
                return ids.contains(player->name());
            });
    }
    Players players(const QVector<QString> &names, const IModelsDbContext *dbContext) const override
    {
        return dbContext->models([names](IModel<QUuid>* m){
                auto player = dynamic_cast<IPlayerModel*>(m);
                return names.contains(player->name());
            });
    }
private:
    IModel<QUuid> *model(const int &index, const QVector<IModel<QUuid> *> &models) const
    {
        if(index < 0 || index >= models.count())
            return nullptr;
        return models.at(index);
    }
    IModel<QUuid> *model(const QUuid &id, const QVector<IModel<QUuid> *> &models) const
    {
        for (auto &model : models)
        {
            if(model->id() == id)
                return model;
        }
        return nullptr;
    }
};
#endif // GETPLAYERDATAFROMDB_H
