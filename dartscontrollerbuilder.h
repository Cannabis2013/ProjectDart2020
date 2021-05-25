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
#include "scorecalculator.h"
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
#include "dartsmultiattemptjsonservice.h"
#include "dartsplayerpointservice.h"
#include "assembledartsscorebyjson.h"
#include "assembledartsscoresbyjson.h"
#include "assembledartsplayersbyjson.h"
#include "assembledartsplayerbyjson.h"
#include "determinecontrollerstatebywinnerid.h"
#include "assembledartsscoreindexesbyjson.h"
#include "addaccumulatedscoretodartsscore.h"
#include "assembledartsscoreturnvalues.h"
#include "buildDartsPointTurnValues.h"
#include "dartscontrollerpointbuilder.h"
#include "addplayernametocontrollerpoint.h"
#include "addplayerscoretocontrollerpoint.h"
#include "builddartssingleattemptindexesbyjson.h"


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

    static DartsControllerBuilder *createInstance();

    AbstractGameController *assembleDartsGameController(const QByteArray& json,
                                                        AbstractApplicationInterface* applicationInterface,
                                                        AbstractModelsService* modelsContext) override;
    virtual void determineTournamentGameMode(const QUuid &tournament,
                                             const int &gameMode) override;

    DartsControllerBuilder *setConnectDartsSingleAttemptPointController(ITernaryService<AbstractDartsPointController *, AbstractApplicationInterface *, AbstractModelsService *, AbstractDartsPointController *> *connectDartsPointController);

    DartsControllerBuilder *setConnectDartsMultiAttemptScoreController(ITernaryService<AbstractDartsScoreController *, AbstractApplicationInterface *, AbstractModelsService *, void> *connectDartsScoreController);

private:
    AbstractDartsPointController* assembleDartsPointController(const QUuid& tournament,
                                                               const QUuid& winnerId,
                                                               const int& keyPoint,
                                                               const int& terminalKeyCode,
                                                               const int& attempts);
    AbstractDartsScoreController* assembleDartsScoreController(const QUuid& tournament,
                                                               const QUuid& winnerId,
                                                               const int& keyPoint,
                                                               const int& terminalKeyCode,
                                                               const int& attempts);
    ITernaryService<AbstractDartsPointController*,
                    AbstractApplicationInterface*,AbstractModelsService*,
                    AbstractDartsPointController*>* _connectDartsSingleAttemptPointController;
    ITernaryService<AbstractDartsScoreController*,
                    AbstractApplicationInterface*,
                    AbstractModelsService*,
                    void>* _connectDartsScoreController;
};


#endif // GAMEBUILDER_H
