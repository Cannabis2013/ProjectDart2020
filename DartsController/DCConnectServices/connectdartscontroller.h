#ifndef CONNECTDARTSCONTROLLER_H
#define CONNECTDARTSCONTROLLER_H

#include "DartControllerContext/ConnectSLAs/iconnectcontroller.h"
#include "DartsController/ControllerSLA/abstractdartscontroller.h"

class ConnectDartsController : public IConnectController
{
public:
    void connectController(AbstractGameController *controller,
                           AbstractApplicationInterface* application,
                           AbstractDartsModelsContext* modelsService,
                           AbstractRouteByHint* routeService) override;
};

#endif // CONNECTDARTSCONTROLLER_H
