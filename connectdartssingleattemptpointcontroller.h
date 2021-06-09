#ifndef CONNECTDARTSPOINTCONTROLLER_H
#define CONNECTDARTSPOINTCONTROLLER_H

#include "iconnectdartspointcontroller.h"

class ConnectDartsSingleAttemptPointController :
        public IConnectDartsPointController
{
public:
    void connectController(AbstractDartsController* controller,
                           AbstractApplicationInterface* application,
                           AbstractModelsService* modelsService) override;
};

#endif // CONNECTDARTSPOINTCONTROLLER_H
