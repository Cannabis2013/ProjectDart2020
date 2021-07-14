#ifndef IGETDARTSPLAYERMODELSFROMDB_H
#define IGETDARTSPLAYERMODELSFROMDB_H

#include "igetplayermodelsfromdb.h"
#include "iplayermodel.h"
#include "iplayermodelsdb.h"

class IGetDartsPlayerModelsFromDb : public IGetPlayerModelsFromDb<DartsModelsContext::IPlayerModel,QUuid,QString,IPlayerModelsDb>
{};
#endif // IGETDARTSPLAYERDATAFROMDB_H
