#ifndef CONNECTDARTSSINGLESCORECONTROLLER_H
#define CONNECTDARTSSINGLESCORECONTROLLER_H

#include "iconnectcontroller.h"
#include "abstractdartsscorecontroller.h"

class ConnectDartsScoreController : public IConnectController
{
public:
    void connectController(AbstractGameController *controller,
                           AbstractApplicationInterface* application,
                           AbstractDartsModelsContext* modelsService,
                           AbstractRouteByDisplayHint* routeService) override;
};

#endif // CONNECTDARTSSINGLESCORECONTROLLER_H
