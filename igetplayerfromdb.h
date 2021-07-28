#ifndef IGETPLAYERSFROMDB_H
#define IGETPLAYERSFROMDB_H

#include "igetmodelsfromdb.h"
#include "imodel.h"
#include "imodelsdbcontext.h"

class IGetPlayersFromDb :
        public IGetModelsFromDb<IModel<QUuid>,QUuid,QString,IModelsDbContext>
{};
#endif // IGETDARTSPLAYERDATAFROMDB_H
