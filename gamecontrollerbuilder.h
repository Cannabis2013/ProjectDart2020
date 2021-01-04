#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "IControllerBuilder.h"
#include "abstractgamecontroller.h"
#include "pointftpcontroller.h"
#include "pointlogisticmanager.h"

class GameControllerBuilder : public IControllerBuilder<AbstractGameController,int>
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
                                                 const int &type,
                                                 const int &contextMode)
    {
        if(contextMode == LocalContext)
        {
            auto controller = createLocalController(gameMode,type);
            return controller;
        }
        return nullptr;
    }

private:

    AbstractGameController* createLocalController(const int &gameMode,
                                                  const int &type)
    {
        if(gameMode == GameModes::FirstToPost)
        {
            auto controller = createFTPController(type);
            return controller;
        }
        else
            return nullptr;
    }

    AbstractGameController* createFTPController(const int &type)
    {
        if(type == InputModes::PointMode)
        {
            auto controller = new PointFTPController();
            controller->setPointLogisticInterface(new PointLogisticManager());
            return controller;
        }
        return nullptr;
    }
};


#endif // GAMEBUILDER_H
