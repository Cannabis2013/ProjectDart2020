#ifndef IGETDARTSPLAYERMODELSFROMDB_H
#define IGETDARTSPLAYERMODELSFROMDB_H

#include "igetplayermodelsfromdb.h"
#include "imodel.h"
#include "idbservice.h"

class IGetDartsPlayerModelsFromDb :
        public IGetPlayerModelsFromDb<IModel<QUuid>,QUuid,QString,IDbService>
{};
#endif // IGETDARTSPLAYERDATAFROMDB_H
