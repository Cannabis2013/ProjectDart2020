#ifndef BUILDDARTSSCORECONTROLLER_H
#define BUILDDARTSSCORECONTROLLER_H


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
    class DartsScoreBuilderService : public AbstractDartsControllerBuilder
    {
        // IControllerBuilder interface
    public:
        // Public types
        enum DisplayHint
        {
            SingleColumn = 0x4,
            MultiColumn = 0x8
        };
        typedef IDartsControllerEntity<QUuid,QString> ControllerEntity;
        typedef IUnaryService<const QByteArray&,
        const ControllerEntity*> ControllerEntityBuilder;
        typedef IBuildControllerService<AbstractDartsScoreController*,
                                        const ControllerEntity*> BuildMultiAttemptScoreController;
        static DartsScoreBuilderService *createInstance();

        AbstractGameController *buildDartsController(const QByteArray& json) override;
        DartsScoreBuilderService *setBuildEntityByJson(ControllerEntityBuilder *newBuildEntityByJson);
        DartsScoreBuilderService *setBuildMultiAttemptScoreController(BuildMultiAttemptScoreController *service);
    private:
        BuildMultiAttemptScoreController* _buildMultiAttemptScoreController;
        ControllerEntityBuilder* _buildEntityByJson;
    };
}

#endif // BUILDDARTSSCORECONTROLLER_H
