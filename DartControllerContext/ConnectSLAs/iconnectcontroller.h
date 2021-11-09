#ifndef ICONNECTDARTSPOINTCONTROLLER_H
#define ICONNECTDARTSPOINTCONTROLLER_H

#include "DartControllerContext/SLAs/abstractgamecontroller.h"
#include "DartApplication/SLAs/AbstractApplicationInterface.h"
#include "DartsModelsContext/SLAs/abstractdartsmodelscontext.h"
#include "DartApplication/RouteSLAs/abstractroutebyhint.h"

class IConnectController
{
public:
    virtual void connect(AbstractGameController* controller,
                                   AbstractApplicationInterface* application,
                                   AbstractDartsModelsContext* modelsService,
                                   AbstractRouteByHint* routeService) = 0;
};

#endif // ICONNECTDARTSPOINTCONTROLLER_H
