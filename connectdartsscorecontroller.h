#ifndef CONNECTDARTSSINGLESCORECONTROLLER_H
#define CONNECTDARTSSINGLESCORECONTROLLER_H

#include "iconnectdartsscorecontroller.h"

class ConnectDartsScoreController : public IConnectDartsScoreController
{
public:
    void connectController(AbstractGameController *controller,
                           AbstractApplicationInterface* application,
                           AbstractModelsService* modelsService,
                           AbstractRouteDartsByDisplayHint* routeService) override;
};

#endif // CONNECTDARTSSINGLESCORECONTROLLER_H
