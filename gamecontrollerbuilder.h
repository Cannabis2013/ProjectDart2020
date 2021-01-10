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

typedef IControllerBuilder<AbstractGameController,QList<int>, QList<QUuid>, QList<QString>,QList<int>> ControllerBuilder;

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



private:

    AbstractGameController* createLocalController(const int &gameMode,
                                                  const QList<int> &params)
    {
        if(gameMode == GameModes::FirstToPost)
        {
            auto controller = createFTPController(params);
            return controller;
        }
        else
            return nullptr;
    }

    AbstractGameController* createFTPController(const QList<int> &params)
    {
        auto keyPoint = params[1];
        auto numberOfThrows = params[2];
        auto terminalKeyCode = params[3];
        auto type = params[4];
        auto playersCount = params[5];
        auto indexes = params.mid(6,5);
        if(type == InputModes::PointMode)
        {
            auto controller = LocalFTPController::createInstance()
                    ->setPointLogisticInterface(PointLogisticManager::createInstance(numberOfThrows,terminalKeyCode))
                    ->setScoreCalculator(new PointScoreCalculator())
                    ->setInputValidator(PointValidator::createInstance(terminalKeyCode))
                    ->setIndexController(PointIndexController::createInstance(numberOfThrows,playersCount,indexes));
            return controller;
        }
        else if(type == InputModes::ScoreMode)
        {
            auto controller = LocalFTPController::createInstance()
                    ->setPointLogisticInterface(PointLogisticManager::createInstance(numberOfThrows,terminalKeyCode))
                    ->setScoreCalculator(new ScoreCalculator())
                    ->setInputValidator(ScoreValidator::createInstance(terminalKeyCode));
            return controller;
        }
        return nullptr;
    }
};


#endif // GAMEBUILDER_H
