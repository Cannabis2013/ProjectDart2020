#ifndef PLAYERMODELSSERVICEBUILDER_H
#define PLAYERMODELSSERVICEBUILDER_H

#include "imodelsservicebuilder.h"
#include "localplayermodelsservice.h"
#include "playersjsondb.h"
#include "iplayermodel.h"
#include <quuid.h>

class PlayerModelsServiceBuilder :
        public IModelsServiceBuilder<IPlayerModelsService<IPlayerModel<QUuid,QString>>>
{
public:
    IPlayerModelsService<IPlayerModel<QUuid,QString>> *buildModelsService() const override;
};

#endif // PLAYERMODELSSERVICEBUILDER_H
