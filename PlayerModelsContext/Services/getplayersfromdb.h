#ifndef GETPLAYERSFROMDB_H
#define GETPLAYERSFROMDB_H

#include "PlayerModelsContext/SLAs/igetplayerfromdb.h"

class GetPlayersFromDb : public IGetPlayersFromDb
{
public:
    const IModel<QUuid> *model(const int &index, const IModelsDbContext *dbService) const override;
    const IModel<QUuid> *model(const QUuid &id, const IModelsDbContext *dbService) const override;
    QVector<const IModel<QUuid> *> models(const QVector<int> &indexes, const IModelsDbContext *dbService) const override;
    QVector<const IModel<QUuid>*> models(const QVector<QUuid> &ids, const IModelsDbContext *dbService) const override;
};

#endif // GETPLAYERDATAFROMDB_H
