#ifndef ICONNECTCONTROLLER_H
#define ICONNECTCONTROLLER_H

#include "abstractdartsscorecontroller.h"
#include "AbstractApplicationInterface.h"
#include "abstractmodelsservice.h"
#include "abstractroutedartsbydisplayhint.h"

class IConnectDartsScoreController
{
public:
    virtual void connectController(AbstractGameController* controller,
                                   AbstractApplicationInterface* application,
                                   AbstractModelsService* modelsService,
                                   AbstractRouteDartsByDisplayHint* routeService) = 0;
};

#endif // ICONNECTCONTROLLER_H
