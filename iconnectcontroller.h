#ifndef ICONNECTDARTSPOINTCONTROLLER_H
#define ICONNECTDARTSPOINTCONTROLLER_H

#include "abstractdartspointcontroller.h"
#include "AbstractApplicationInterface.h"
#include "abstractmodelsservice.h"
#include "abstractroutebydisplayhint.h"

class IConnectController
{
public:
    virtual void connectController(AbstractGameController* controller,
                                   AbstractApplicationInterface* application,
                                   AbstractModelsService* modelsService,
                                   AbstractRouteByDisplayHint* routeService) = 0;
};

#endif // ICONNECTDARTSPOINTCONTROLLER_H
