#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "IControllerBuilder.h"
#include "abstractdartscontroller.h"
#include "scoredartscontroller.h"
#include "pointdartscontroller.h"
// Include services
#include "pointlogisticcontroller.h"
#include "scorelogisticcontroller.h"
#include "pointScoreCalculator.h"
#include "scorecalculator.h"
#include "pointvalidator.h"
#include "ScoreValidator.h"
#include "abstractcontrollerbuilder.h"
#include "dartsscorecontroller.h"
#include "PointIndexController.h"
#include "scoreindexcontroller.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class ControllerBuilder : public AbstractControllerBuilder
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

    AbstractGameController *assembleFTPGameController(const QByteArray& json,
                                                      AbstractApplicationInterface* applicationInterface,
                                                      AbstractModelsContext* modelsContext) override;
    virtual void determineTournamentGameMode(const QUuid &tournament, const int &gameMode) override;

private:
    AbstractDartsController* assembleFtpPointBasedController(const QUuid& tournament,
                                                            const QUuid& winnerId,
                                                            const int& keyPoint,
                                                            const int& terminalKeyCode,
                                                            const int& attempts);
    AbstractDartsController* assembleFtpScoreBasedController(const QUuid& tournament,
                                                            const QUuid& winnerId,
                                                            const int& keyPoint,
                                                            const int& terminalKeyCode,
                                                            const int& attempts);
    void connectFTPController(AbstractDartsController* controller,
                              AbstractApplicationInterface*  applicationInterface,
                              AbstractModelsContext* modelsContext);
};


#endif // GAMEBUILDER_H
