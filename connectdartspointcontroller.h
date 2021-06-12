#ifndef CONNECTDARTSPOINTCONTROLLER_H
#define CONNECTDARTSPOINTCONTROLLER_H

#include "iconnectdartspointcontroller.h"

class ConnectDartsPointController :
        public IConnectDartsPointController
{
public:
    void connectController(AbstractDartsController* controller,
                           AbstractApplicationInterface* application,
                           AbstractModelsService* modelsService,
                           AbstractRouteDartsByDisplayHint* routeService) override;
};

#endif // CONNECTDARTSPOINTCONTROLLER_H
