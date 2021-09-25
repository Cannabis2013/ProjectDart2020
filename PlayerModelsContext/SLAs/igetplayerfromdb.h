#ifndef IGETPLAYERSFROMDB_H
#define IGETPLAYERSFROMDB_H

#include "ModelsContext/MCModelsSLAs/imodel.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include "iplayermodel.h"

#include <qvector.h>

class IGetPlayersFromDb
{
public:
    virtual const IModel<QUuid> *model(const int &index, const IModelsDbContext *dbService) const = 0;
    virtual const IModel<QUuid> *model(const QUuid &id, const IModelsDbContext *dbService) const = 0;
    virtual QVector<const IModel<QUuid>*> models(const QVector<int> &indexes, const IModelsDbContext *dbService) const = 0;
    virtual QVector<const IModel<QUuid>*> models(const QVector<QUuid> &ids, const IModelsDbContext *dbService) const = 0;
};
#endif // IGETDARTSPLAYERDATAFROMDB_H
