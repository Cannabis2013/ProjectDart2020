#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "IControllerBuilder.h"
#include "abstractgamecontroller.h"
#include "localftpcontroller.h"
// Include services
#include "pointlogisticmanager.h"
#include "pointScoreCalculator.h"
#include "scorecalculator.h"
#include "pointvalidator.h"
#include "ScoreValidator.h"
#include "PointIndexController.h"
#include "ftpscorecontroller.h"

typedef IControllerBuilder<AbstractGameController,QUuid,QList<int>, QList<QUuid>, QList<QString>,QList<int>> ControllerBuilder;

class GameControllerBuilder : public ControllerBuilder
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

    enum ContextMode {
        LocalContext = 0x7,
        RemoteContext = 0x8
    };

    virtual AbstractGameController *assembleFTPGameController(const QUuid &tournament,
                                                              const QUuid &winner,
                                                              const QList<int> &parameters,
                                                              const QList<QUuid> &userIds,
                                                              const QList<QString> &userNames,
                                                              const QList<int> &userScores) override
    {
        auto numberOfThrows = parameters[2];
        auto terminalKeyCode = parameters[3];
        auto type = parameters[4];
        auto indexes = parameters.mid(5,5);
        auto playersCount = userIds.count();
        if(type == InputModes::PointMode)
        {
            auto controller = LocalFTPController::createInstance(tournament)
                    ->setPointLogisticInterface(PointLogisticManager::createInstance(numberOfThrows,terminalKeyCode))
                    ->setScoreCalculator(new PointScoreCalculator())
                    ->setInputValidator(PointValidator::createInstance(terminalKeyCode))
                    ->setIndexController(PointIndexController::createInstance(numberOfThrows,playersCount,indexes))
                    ->setScoreController(FTPScoreController::createInstance(userIds,userNames,userScores));
            return controller;
        }
        else if(type == InputModes::ScoreMode)
        {
            auto controller = LocalFTPController::createInstance(tournament)
                    ->setPointLogisticInterface(PointLogisticManager::createInstance(numberOfThrows,terminalKeyCode))
                    ->setScoreCalculator(new ScoreCalculator())
                    ->setInputValidator(ScoreValidator::createInstance(terminalKeyCode))
                    ->setScoreController(FTPScoreController::createInstance(userIds,userNames,userScores));
            return controller;
        }
        return nullptr;
    }
};


#endif // GAMEBUILDER_H
