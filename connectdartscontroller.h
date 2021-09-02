#ifndef CONNECTDARTSCONTROLLER_H
#define CONNECTDARTSCONTROLLER_H

#include "iconnectcontroller.h"
#include "abstractdartscontroller.h"

class ConnectDartsController : public IConnectController
{
public:
    void connectController(AbstractGameController *controller,
                           AbstractApplicationInterface* application,
                           AbstractDartsModelsContext* modelsService,
                           AbstractRouteByDisplayHint* routeService) override;
};

#endif // CONNECTDARTSCONTROLLER_H
