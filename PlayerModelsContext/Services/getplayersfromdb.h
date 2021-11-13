#ifndef GETPLAYERSFROMDB_H
#define GETPLAYERSFROMDB_H
#include "PlayerModelsContext/DbSLAs/igetplayerfromdb.h"
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
class GetPlayersFromDb : public IGetPlayersFromDb
{
public:
    virtual Player *player(const QUuid &id, const IModelsDbContext *dbService) const override
    {
        auto players = dbService->models();
        return model(id,players);
    }
    QVector<IModel<QUuid> *> players(const QVector<int> &indexes, const IModelsDbContext *dbService) const override
    {
        auto models = dbService->models();
        QVector<IModel<QUuid>*> playerModels;
        for (const auto &index : indexes)
            playerModels << model(index,models);
        return playerModels;
    }
    virtual QVector<IModel<QUuid> *> players(const QVector<QUuid> &ids, const IModelsDbContext *dbService) const override
    {
        auto models = dbService->models();
        QVector<IModel<QUuid>*> playerModels;
        for (const auto &id : ids)
            playerModels << model(id,models);
        return playerModels;
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
