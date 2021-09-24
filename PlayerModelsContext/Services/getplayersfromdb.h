#ifndef GETPLAYERSFROMDB_H
#define GETPLAYERSFROMDB_H

#include "PlayerModelsContext/SLAs/igetplayerfromdb.h"

class GetPlayersFromDb : public IGetPlayersFromDb
{
public:
    virtual const PlayerModel *model(const int &index, const DbService *dbService) const override;
    virtual const PlayerModel *model(const Id &id, const DbService *dbService) const override;
    virtual QVector<const PlayerModel *> models(const QVector<int> &indexes, const DbService *dbService) const override;
    QVector<const PlayerModel*> models(const QVector<Id> &ids, const DbService *dbService) const override;
};

#endif // GETPLAYERDATAFROMDB_H
