#ifndef IGETPLAYERSFROMDB_H
#define IGETPLAYERSFROMDB_H

#include "igetmodelsfromdb.h"
#include "ModelsContext/imodel.h"
#include "ModelsContext/imodelsdbcontext.h"

class IGetPlayersFromDb :
        public IGetModelsFromDb<IModel<QUuid>,QUuid,QString,IModelsDbContext>
{};
#endif // IGETDARTSPLAYERDATAFROMDB_H
