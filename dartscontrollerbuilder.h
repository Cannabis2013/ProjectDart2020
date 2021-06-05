#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "IControllerBuilder.h"
#include "abstractdartscontroller.h"
#include "dartsscoremultiattempt.h"
#include "dartspointsingleattempt.h"
// Include services
#include "dartspointlogisticcontroller.h"
#include "dartsscorelogisticcontroller.h"
#include "DartsPointCalculator.h"
#include "pointvalidator.h"
#include "ScoreValidator.h"
#include "abstractdartscontrollerbuilder.h"
#include "dartsplayerscoreservice.h"
#include "PointIndexController.h"
#include "scoreindexcontroller.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "abstractdartsscorecontroller.h"
#include "abstractdartspointcontroller.h"
#include "iternaryservice.h"
#include "dartspointjsonservice.h"
#include "dartsscorejsonbuilderservice.h"
#include "dartsplayerpointservice.h"
#include "determinecontrollerstatebywinnerid.h"
#include "addaccumulatedscoretodartsscore.h"
#include "assembledartsscoreturnvalues.h"
#include "buildDartsPointTurnValues.h"
#include "dartscontrollerpointbuilder.h"
#include "dartscontrollerpointmodelsservice.h"
#include "DartsIndexesBuilderService.h"
#include "dartsplayermodelbuilderservice.h"
#include "dartsscoremodelsbuilderservice.h"
#include "dartsscoreindexesbuilderservice.h"
#include "DartsScoreJsonExtractor.h"
#include "dartsplayerbuilderservice.h"
#include "idartscontrollerentity.h"
#include "BuildDartsControllerEntity.h"

namespace DartsBuilderContext {
    class DartsControllerBuilder : public AbstractDartsControllerBuilder
    {
        // IControllerBuilder interface
    public:
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

        static DartsControllerBuilder *createInstance();

        AbstractGameController *assembleDartsGameController(const QByteArray& json,
                                                            AbstractApplicationInterface* applicationInterface,
                                                            AbstractModelsService* modelsContext) override;
        virtual void determineTournamentGameMode(const QUuid &tournament,
                                                 const int &gameMode) override;

        DartsControllerBuilder *setConnectDartsSingleAttemptPointController(ITernaryService<AbstractDartsPointController *, AbstractApplicationInterface *, AbstractModelsService *, AbstractDartsPointController *> *connectDartsPointController);

        DartsControllerBuilder *setConnectDartsMultiAttemptScoreController(ITernaryService<AbstractDartsScoreController *, AbstractApplicationInterface *, AbstractModelsService *, void> *connectDartsScoreController);

    private:
        AbstractDartsPointController* assembleDartsPointController(const ControllerEntity* entity);
        AbstractDartsScoreController* assembleDartsScoreController(const ControllerEntity* entity);
        ITernaryService<AbstractDartsPointController*,
                        AbstractApplicationInterface*,AbstractModelsService*,
                        AbstractDartsPointController*>* _connectDartsSingleAttemptPointController;
        ITernaryService<AbstractDartsScoreController*,
                        AbstractApplicationInterface*,
                        AbstractModelsService*,
                        void>* _connectDartsScoreController;
        IUnaryService<const QByteArray&,
                      const ControllerEntity*>* _buildEntityByJson = BuildDartsControllerEntity::createInstance();
    };
}



#endif // GAMEBUILDER_H
