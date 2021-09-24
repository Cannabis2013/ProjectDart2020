#ifndef IGETPLAYERSFROMDB_H
#define IGETPLAYERSFROMDB_H

#include "igetmodelsfromdb.h"
#include "ModelsContext/MCModelsSLAs/imodel.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class IGetPlayersFromDb :
        public IGetModelsFromDb<IModel<QUuid>,QUuid,QString,IModelsDbContext>
{};
#endif // IGETDARTSPLAYERDATAFROMDB_H
