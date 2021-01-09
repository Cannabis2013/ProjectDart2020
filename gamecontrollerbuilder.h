#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "IControllerBuilder.h"
#include "abstractgamecontroller.h"
#include "localftpcontroller.h"
#include "pointlogisticmanager.h"
#include "pointScoreCalculator.h"
#include "scorecalculator.h"
#include "pointvalidator.h"

typedef IControllerBuilder<AbstractGameController,int, int[]> ControllerBuilder;

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

    AbstractGameController * buildGameController(const int &gameMode,
                                                 const int (&params)[],
                                                 const int &contextMode)
    {
        if(contextMode == LocalContext)
        {
            auto controller = createLocalController(gameMode,params);
            return controller;
        }
        return nullptr;
    }

private:

    AbstractGameController* createLocalController(const int &gameMode,
                                                  const int (&params)[])
    {
        if(gameMode == GameModes::FirstToPost)
        {
            auto controller = createFTPController(params);
            return controller;
        }
        else
            return nullptr;
    }

    AbstractGameController* createFTPController(const int (&params)[])
    {
        auto type = params[0];
        auto keyPoint = params[1];
        auto terminalKeyCode = params[2];
        auto numberOfThrows = params[3];
        if(type == InputModes::PointMode)
        {
            auto controller = LocalFTPController::createInstance(keyPoint,numberOfThrows)
                    ->setPointLogisticInterface(PointLogisticManager::createInstance(numberOfThrows,terminalKeyCode))
                    ->setScoreCalculator(new PointScoreCalculator())
                    ->setScoreValidator(new PointValidator(terminalKeyCode));
            return controller;
        }
        else if(type == InputModes::ScoreMode)
        {
            auto controller = LocalFTPController::createInstance(keyPoint,numberOfThrows)
                    ->setPointLogisticInterface(PointLogisticManager::createInstance(numberOfThrows,terminalKeyCode))
                    ->setScoreCalculator(new ScoreCalculator());
            return controller;
        }
        return nullptr;
    }
};


#endif // GAMEBUILDER_H
