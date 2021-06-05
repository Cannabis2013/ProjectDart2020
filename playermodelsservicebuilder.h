#ifndef PLAYERMODELSSERVICEBUILDER_H
#define PLAYERMODELSSERVICEBUILDER_H

#include "imodelsservicebuilder.h"
#include "localplayermodelsservice.h"
#include "playermodelsjsonassembler.h"
#include "playermodelsjsonextractor.h"
#include "playersjsondb.h"
#include "iplayermodel.h"
#include <quuid.h>

namespace DartsModelsContext {
    class PlayerModelsServiceBuilder :
            public IModelsServiceBuilder<IPlayerModelsService>
    {
    public:
        IPlayerModelsService *buildModelsService() const override;
    };
}


#endif // PLAYERMODELSSERVICEBUILDER_H
