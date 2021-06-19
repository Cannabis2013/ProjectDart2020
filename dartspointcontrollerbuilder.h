#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "dartsscorecontroller.h"
// Include services
#include "abstractdartscontrollerbuilder.h"
#include "dartsscoremodelsbuilderservice.h"
#include "abstractdartsscorecontroller.h"
#include "abstractdartspointcontroller.h"
#include "iternaryservice.h"
#include "dartsplayermodelbuilderservice.h"
#include "idartscontrollerentity.h"
#include "BuildDartsControllerEntity.h"
#include <quuid.h>
#include "defaultdartspointcontroller.h"

namespace DartsBuilderContext {
    class DartsPointControllerBuilder : public AbstractDartsControllerBuilder
    {
        // IControllerBuilder interface
    public:
        // Public types
        typedef IDartsControllerEntity<QUuid,QString> ControllerEntity;
        typedef IUnaryService<const QByteArray&,
                              const ControllerEntity*> ControllerEntityBuilder;
        static DartsPointControllerBuilder *createInstance();
        AbstractGameController *buildDartsController(const QByteArray& json) override;
        DartsPointControllerBuilder *setBuildEntityByJson(ControllerEntityBuilder *newBuildEntityByJson);
    private:
        ControllerEntityBuilder* _buildEntityByJson;
    };
}

#endif // GAMEBUILDER_H
