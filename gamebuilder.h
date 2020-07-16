#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "IControllerBuilder.h"
#include "abstractcontrollerinterface.h"

#include "localfirsttopost.h"

class GameBuilder : public IControllerBuilder<AbstractControllerInterface,int>
{
    // IControllerBuilder interface
public:
    enum GameModes {
        FirstToPost = 0x1,
        RoundBased =0x2,
        CircularDart = 0x3
    };

    enum ContextMode {LocalContext = 0x4, RemoteContext = 0x5};

    AbstractControllerInterface * buildController(const int &mode, const int&contextMode) override
    {
        if(mode == FirstToPost && contextMode == LocalContext)
            return new LocalFirstToPost();

        return nullptr;
    }
};


#endif // GAMEBUILDER_H
