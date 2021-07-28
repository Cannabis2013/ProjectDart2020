#include "getplayersfromdb.h"

const GetPlayersFromDb::PlayerModel *GetPlayersFromDb::model(const int &index,
                                                                                       const DbService *dbService) const
{
    auto model = dbService->model(index);
    return model;
}

const GetPlayersFromDb::PlayerModel *GetPlayersFromDb::model(const Id &id,
                                                                                       const DbService *dbService) const
{
    auto models = dbService->models();
    for (const auto &model : models) {
        if(model->id() == id)
            return model;
    }
    return nullptr;
}

QVector<const GetPlayersFromDb::PlayerModel *> GetPlayersFromDb::models(const QVector<int> &indexes,
                                                                                                  const DbService *dbService) const
{
    QVector<const PlayerModel*> playerModels;
    for (const auto &index : indexes) {
        playerModels << model(index,dbService);
    }
    return playerModels;
}

QVector<const GetPlayersFromDb::PlayerModel *> GetPlayersFromDb::models(const QVector<Id> &ids,
                                                                                                  const DbService *dbService) const
{
    QVector<const PlayerModel*> list;
    for (const auto &id : ids)
        list << model(id,dbService);
    return list;
}
