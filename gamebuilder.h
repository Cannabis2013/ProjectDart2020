#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "IControllerBuilder.h"
#include "abstractgamecontroller.h"
#include "localftpcontroller.h"
#include "pointlogisticmanager.h"

class GameBuilder : public IControllerBuilder<AbstractGameController,int>
{
    // IControllerBuilder interface
public:
    enum GameModes {
        FirstToPost = 0x1,
        RoundBased =0x2,
        CircularDart = 0x3
    };

    enum ContextMode {LocalContext = 0x4, RemoteContext = 0x5};

    AbstractGameController * buildController(const int &mode, const int&contextMode)
    {
        if(mode == FirstToPost && contextMode == LocalContext)
        {
            auto controller = new LocalFTPController();
            controller->setPointLogisticInterface(new PointLogisticManager());
            return controller;
        }
        return nullptr;
    }
};


#endif // GAMEBUILDER_H
