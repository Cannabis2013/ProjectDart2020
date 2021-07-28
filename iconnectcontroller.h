#ifndef ICONNECTDARTSPOINTCONTROLLER_H
#define ICONNECTDARTSPOINTCONTROLLER_H

#include "abstractdartspointcontroller.h"
#include "AbstractApplicationInterface.h"
#include "abstractdartsmodelscontext.h"
#include "abstractroutebydisplayhint.h"

class IConnectController
{
public:
    virtual void connectController(AbstractGameController* controller,
                                   AbstractApplicationInterface* application,
                                   AbstractDartsModelsContext* modelsService,
                                   AbstractRouteByDisplayHint* routeService) = 0;
};

#endif // ICONNECTDARTSPOINTCONTROLLER_H
