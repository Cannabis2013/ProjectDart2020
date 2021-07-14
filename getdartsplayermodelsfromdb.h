#ifndef GETDARTSPLAYERMODELSFROMDB_H
#define GETDARTSPLAYERMODELSFROMDB_H

#include "igetdartsplayermodelsfromdb.h"

class GetDartsPlayerModelsFromDb : public IGetDartsPlayerModelsFromDb
{
public:
    virtual const PlayerModel *playerModel(const int &index, const DbService *dbService) const override;
    virtual const PlayerModel *playerModel(const Id &id, const DbService *dbService) const override;
    virtual QVector<const PlayerModel *> playerModels(const QVector<int> &indexes, const DbService *dbService) const override;
    QVector<const PlayerModel*> playerModels(const QVector<Id> &ids, const DbService *dbService) const override;
};

#endif // GETPLAYERDATAFROMDB_H
