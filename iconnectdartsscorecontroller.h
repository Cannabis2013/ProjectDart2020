#ifndef ICONNECTCONTROLLER_H
#define ICONNECTCONTROLLER_H

#include "abstractdartsscorecontroller.h"
#include "AbstractApplicationInterface.h"
#include "abstractmodelsservice.h"

class IConnectDartsScoreController
{
public:
    virtual void connectController(AbstractDartsController* controller,
                                   AbstractApplicationInterface* application,
                                   AbstractModelsService* modelsService) = 0;
};

#endif // ICONNECTCONTROLLER_H
