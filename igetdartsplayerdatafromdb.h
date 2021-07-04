#ifndef IGETDARTSPLAYERDATAFROMDB_H
#define IGETDARTSPLAYERDATAFROMDB_H

#include "igetplayerdatafromdb.h"
#include "iplayermodel.h"
#include "iplayermodelsdb.h"

class IGetDartsPlayerDataFromDb : public IGetPlayerDataFromDb<DartsModelsContext::IPlayerModel,QUuid,QString,IPlayerModelsDb>
{};
#endif // IGETDARTSPLAYERDATAFROMDB_H
