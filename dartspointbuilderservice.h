#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "dartsscoremultiattempt.h"
// Include services
#include "abstractdartscontrollerbuilder.h"
#include "dartsscoremodelsbuilderservice.h"
#include "abstractdartsscorecontroller.h"
#include "abstractdartspointcontroller.h"
#include "iternaryservice.h"
#include "dartsplayermodelbuilderservice.h"
#include "idartscontrollerentity.h"
#include "BuildDartsControllerEntity.h"
#include "ibuildcontrollerservice.h"

namespace DartsBuilderContext {
    class DartsPointBuilderService : public AbstractDartsControllerBuilder
    {
        // IControllerBuilder interface
    public:
        // Public types
        typedef IDartsControllerEntity<QUuid,QString> ControllerEntity;
        typedef IUnaryService<const QByteArray&,
                              const ControllerEntity*> ControllerEntityBuilder;
        typedef IBuildControllerService<AbstractDartsPointController*,
                                        const ControllerEntity*> BuildPointController;
        static DartsPointBuilderService *createInstance();
        AbstractGameController *buildDartsController(const QByteArray& json) override;
        DartsPointBuilderService *setBuildEntityByJson(ControllerEntityBuilder *newBuildEntityByJson);
        DartsPointBuilderService * setBuildSingleAttemptPointController(BuildPointController *service);
    private:
        BuildPointController* _buildControllerService;
        ControllerEntityBuilder* _buildEntityByJson;
    };
}

#endif // GAMEBUILDER_H
