#ifndef CONNECTDARTSPOINTCONTROLLER_H
#define CONNECTDARTSPOINTCONTROLLER_H

#include "iconnectcontroller.h"

class ConnectDartsPointController :
        public IConnectController
{
public:
    void connectController(AbstractGameController* controller,
                           AbstractApplicationInterface* application,
                           AbstractDartsModelsContext* modelsService,
                           AbstractRouteByDisplayHint* routeService) override;
};

#endif // CONNECTDARTSPOINTCONTROLLER_H
