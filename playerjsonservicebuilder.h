#ifndef PLAYERJSONSERVICEBUILDER_H
#define PLAYERJSONSERVICEBUILDER_H

#include "imodelsservicebuilder.h"
#include "iplayermodel.h"
#include "iplayermodelsjsonservice.h"
#include "playermodelsjsonservice.h"
#include "getplayerindexesfromjson.h"
#include "jsonarrayfromplayernamesandids.h"
#include "assemblejsonfromplayeridandname.h"
#include "getdeleteplayerindexfromjson.h"
#include "assembleplayermodelfromjson.h"
#include "getwinneridbyjson.h"
namespace DartsModelsContext {
    class PlayerJsonServiceBuilder : public
            IModelsServiceBuilder<IPlayerModelsJsonService<IPlayerModel,QUuid,QString,QByteArray>>
    {
    public:
        virtual ServiceInterface *buildModelsService() const override;
    };
}

#endif // PLAYERJSONSERVICEBUILDER_H
