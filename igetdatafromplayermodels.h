#ifndef IGETDATAFROMPLAYERMODELS_H
#define IGETDATAFROMPLAYERMODELS_H

#include "iplayermodellistservice.h"
#include "quuid.h"
#include "iplayermodel.h"

class IGetDataFromPlayerModels : public IPlayerModelListService<DartsModelsContext::IPlayerModel,QUuid,QString>
{};
#endif // IDARTSPLAYERLISTSERVICE_H