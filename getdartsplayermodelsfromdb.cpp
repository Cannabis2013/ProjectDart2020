#include "getdartsplayermodelsfromdb.h"

const GetDartsPlayerModelsFromDb::PlayerModel *GetDartsPlayerModelsFromDb::playerModel(const int &index,
                                                                                const DbService *dbService) const
{
    auto model = dbService->model(index);
    return model;
}

const GetDartsPlayerModelsFromDb::PlayerModel *GetDartsPlayerModelsFromDb::playerModel(const Id &id,
                                                                                       const DbService *dbService) const
{
    auto models = dbService->models();
    for (const auto &model : models) {
        if(model->id() == id)
            return model;
    }
    throw "Model not found";
}

QVector<const GetDartsPlayerModelsFromDb::PlayerModel *> GetDartsPlayerModelsFromDb::playerModels(const QVector<int> &indexes,
                                                                                                  const DbService *dbService) const
{
    QVector<const PlayerModel*> playerModels;
    for (const auto &index : indexes) {
        playerModels << playerModel(index,dbService);
    }
    return playerModels;
}

QVector<const GetDartsPlayerModelsFromDb::PlayerModel *> GetDartsPlayerModelsFromDb::playerModels(const QVector<Id> &ids,
                                                                                                  const DbService *dbService) const
{
    QVector<const PlayerModel*> list;
    for (const auto &id : ids)
        list << playerModel(id,dbService);
    return list;
}
