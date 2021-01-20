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
#include "abstractcontrollerbuilder.h"
typedef IControllerBuilder<AbstractGameController,QUuid,QList<int>, QList<QUuid>, QList<QString>,QList<int>> ControllerBuilder;

class GameControllerBuilder : public AbstractControllerBuilder
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
                                                              const QList<int> &values,
                                                              const QList<QUuid> &userIds,
                                                              const QList<QString> &userNames) override
    {
        auto numberOfThrows = values[2];
        auto terminalKeyCode = values[3];
        auto type = values[4];
        auto indexes = values.mid(5,5);
        auto userScores = values.mid(10);
        auto playersCount = userIds.count();
        if(type == InputModes::PointMode)
        {
            auto controller = LocalFTPController::createInstance(tournament)
                    ->setPointLogisticInterface(PointLogisticManager::createInstance(numberOfThrows,terminalKeyCode))
                    ->setScoreCalculator(new PointScoreCalculator())
                    ->setInputValidator(PointValidator::createInstance(terminalKeyCode))
                    ->setIndexController(PointIndexController::createInstance(numberOfThrows,playersCount,indexes))
                    ->setScoreController(FTPScoreController::createInstance(userIds,userNames,userScores,winner));
            return controller;
        }
        else if(type == InputModes::ScoreMode)
        {
            auto controller = LocalFTPController::createInstance(tournament)
                    ->setPointLogisticInterface(PointLogisticManager::createInstance(numberOfThrows,terminalKeyCode))
                    ->setScoreCalculator(new ScoreCalculator())
                    ->setInputValidator(ScoreValidator::createInstance(terminalKeyCode))
                    ->setScoreController(FTPScoreController::createInstance(userIds,userNames,userScores,winner));
            return controller;
        }
        return nullptr;
    }
    virtual void handleRecieveGameMode(const QUuid &tournament, const int &gameMode) override
    {
        if(gameMode == GameModes::FirstToPost)
            emit requestFTPDetails(tournament);
    }
};


#endif // GAMEBUILDER_H
