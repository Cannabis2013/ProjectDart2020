#include "getdartsplayerdatafromdb.h"

const GetDartsPlayerDataFromDb::PlayerModel *GetDartsPlayerDataFromDb::playerModel(const int &index,
                                                                                const DbService *dbService) const
{
    auto model = dbService->model(index);
    return model;
}

const GetDartsPlayerDataFromDb::PlayerModel *GetDartsPlayerDataFromDb::playerModel(const Id &id, const DbService *dbService) const
{
    auto models = dbService->models();
    for (const auto &model : models) {
        if(model->id() == id)
            return model;
    }
    throw "Model not found";
}

const GetDartsPlayerDataFromDb::String GetDartsPlayerDataFromDb::playerName(const Id &playerId, const DbService *dbService) const
{
    auto playerModel = this->playerModel(playerId,dbService);
    return playerModel->playerName();
}

const QVector<GetDartsPlayerDataFromDb::String> GetDartsPlayerDataFromDb::playerNames(const QVector<Id> &playerIds, const DbService *dbService) const
{
    QVector<String> playerNames;
    for (const auto &playerId : playerIds) {
        auto playerModel = this->playerModel(playerId,dbService);
        playerNames << playerModel->playerName();
    }
    return playerNames;
}

QVector<GetDartsPlayerDataFromDb::Id> GetDartsPlayerDataFromDb::playerIds(const DbService *dbService) const
{
    auto playerModels = dbService->models();
    auto playerIds = getPlayerIds(playerModels);
    return playerIds;
}

int GetDartsPlayerDataFromDb::playersCount(const DbService *dbService) const
{
    auto models = dbService->models();
    auto count = models.count();
    return count;
}

QVector<const GetDartsPlayerDataFromDb::PlayerModel *> GetDartsPlayerDataFromDb::playerModels(const QVector<int> &indexes,
                                                                                              const DbService *dbService) const
{
    QVector<const PlayerModel*> playerModels;
    for (const auto &index : indexes) {
        playerModels << playerModel(index,dbService);
    }
    return playerModels;
}

QVector<GetDartsPlayerDataFromDb::Id> GetDartsPlayerDataFromDb::getPlayerIds(const QVector<const PlayerModel *> &models) const
{
    QVector<Id> ids;
    for (const auto &model : models)
        ids << model->id();
    return ids;
}
