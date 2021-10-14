#ifndef GETPLAYERSFROMDB_H
#define GETPLAYERSFROMDB_H

#include "PlayerModelsContext/DbSLAs/igetplayerfromdb.h"

class GetPlayersFromDb : public IGetPlayersFromDb
{
public:
    QVector<IModel<QUuid> *> models(const QVector<int> &indexes, const IModelsDbContext *dbService) const override
    {
        QVector<IModel<QUuid>*> playerModels;
        for (const auto &index : indexes) {
            playerModels << model(index,dbService);
        }
        return playerModels;
    }
private:
    IModel<QUuid> *model(const int &index, const IModelsDbContext *dbService) const
    {
        auto models = dbService->models();
        return models.at(index);
    }
};

#endif // GETPLAYERDATAFROMDB_H
