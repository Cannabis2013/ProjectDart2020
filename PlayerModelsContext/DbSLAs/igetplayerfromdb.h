#ifndef IGETPLAYERSFROMDB_H
#define IGETPLAYERSFROMDB_H

#include "ModelsContext/MCModelsSLAs/imodel.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "iplayermodel.h"

#include <qvector.h>

class IGetPlayersFromDb
{
public:
    virtual QVector<IModel<QUuid>*> models(const QVector<int> &indexes, const IModelsDbContext *dbService) const = 0;
};
#endif // IGETDARTSPLAYERDATAFROMDB_H
