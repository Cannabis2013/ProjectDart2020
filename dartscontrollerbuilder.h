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
    class DartsControllerBuilder : public AbstractDartsControllerBuilder
    {
        // IControllerBuilder interface
    public:
        // Public types
        enum GameModes {
            FirstToPost = 0x1,
            RoundBased =0x2,
            CircularDart = 0x3
        };

        enum InputModes {
            PointMode = 0x5,
            ScoreMode = 0x6
        };

        enum DisplayHint
        {
            SingleColumn = 0x4,
            MultiColumn = 0x8
        };

        enum ContextMode {
            LocalContext = 0x7,
            RemoteContext = 0x8
        };

        typedef IDartsControllerEntity<QUuid,QString> ControllerEntity;
        typedef IUnaryService<const QByteArray&,
        const ControllerEntity*> ControllerEntityBuilder;
        typedef ITernaryService<AbstractDartsPointController*,
                                AbstractApplicationInterface*,
                                AbstractModelsService*,
                                AbstractDartsPointController*> ConnectSingleAttempPointController;
        typedef ITernaryService<AbstractDartsScoreController*,
                                AbstractApplicationInterface*,
                                AbstractModelsService*,
                                void> ConnectMultiAttemptScoreController;
        typedef IBuildControllerService<AbstractDartsPointController*,
                                        const ControllerEntity*> BuildSingleAttemptPointController;
        typedef IBuildControllerService<AbstractDartsScoreController*,
                                        const ControllerEntity*> BuildMultiAttemptScoreController;


        static DartsControllerBuilder *createInstance();

        AbstractGameController *assembleDartsGameController(const QByteArray& json,
                                                            AbstractApplicationInterface* applicationInterface,
                                                            AbstractModelsService* modelsContext) override;
        DartsControllerBuilder *setConnectDartsSingleAttemptPointController(ConnectSingleAttempPointController *connectDartsPointController);
        DartsControllerBuilder *setConnectDartsMultiAttemptScoreController(ITernaryService<AbstractDartsScoreController *, AbstractApplicationInterface *, AbstractModelsService *, void> *connectDartsScoreController);
        DartsControllerBuilder *setBuildEntityByJson(ControllerEntityBuilder *newBuildEntityByJson);
        DartsControllerBuilder * setBuildSingleAttemptPointController(BuildSingleAttemptPointController *newBuildSingleAttemptPointController);
        DartsControllerBuilder * setBuildMultiAttemptScoreController(BuildMultiAttemptScoreController *newBuildMultiAttemptScoreController);
    private:
        BuildSingleAttemptPointController* _buildSingleAttemptPointController;
        BuildMultiAttemptScoreController* _buildMultiAttemptScoreController;
        ConnectSingleAttempPointController* _connectDartsSingleAttemptPointController;
        ConnectMultiAttemptScoreController* _connectDartsScoreController;
        ControllerEntityBuilder* _buildEntityByJson;
    };
}



#endif // GAMEBUILDER_H
