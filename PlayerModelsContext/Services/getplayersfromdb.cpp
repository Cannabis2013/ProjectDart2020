#include "PlayerModelsContext/Services/getplayersfromdb.h"

const IModel<QUuid> *GetPlayersFromDb::model(const int &index, const IModelsDbContext *dbService) const
{
    auto model = dbService->model(index);
    return model;
}

const IModel<QUuid> *GetPlayersFromDb::model(const QUuid &id, const IModelsDbContext *dbService) const
{
    auto models = dbService->models();
    for (const auto &model : models) {
        if(model->id() == id)
            return model;
    }
    return nullptr;
}

QVector<const IModel<QUuid>*> GetPlayersFromDb::models(const QVector<int> &indexes, const IModelsDbContext *dbService) const
{
    QVector<const IModel<QUuid>*> playerModels;
    for (const auto &index : indexes) {
        playerModels << model(index,dbService);
    }
    return playerModels;
}

QVector<const IModel<QUuid> *> GetPlayersFromDb::models(const QVector<QUuid> &ids, const IModelsDbContext *dbService) const
{
    QVector<const IModel<QUuid>*> list;
    for (const auto &id : ids)
        list << model(id,dbService);
    return list;
}
