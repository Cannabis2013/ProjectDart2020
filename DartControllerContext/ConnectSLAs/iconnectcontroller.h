#ifndef ICONNECTDARTSPOINTCONTROLLER_H
#define ICONNECTDARTSPOINTCONTROLLER_H

#include "DartControllerContext/SLAs/abstractgamecontroller.h"
#include "DartApplication/SLAs/AbstractApplicationInterface.h"
#include "DartsModelsContext/SLAs/abstractdartsmodelscontext.h"
#include "DartApplication/RouteSLAs/abstractroutebydisplayhint.h"

class IConnectController
{
public:
    virtual void connectController(AbstractGameController* controller,
                                   AbstractApplicationInterface* application,
                                   AbstractDartsModelsContext* modelsService,
                                   AbstractRouteByDisplayHint* routeService) = 0;
};

#endif // ICONNECTDARTSPOINTCONTROLLER_H
