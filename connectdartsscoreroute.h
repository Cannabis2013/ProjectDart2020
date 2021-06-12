#ifndef CONNECTDARTSSCOREROUTE_H
#define CONNECTDARTSSCOREROUTE_H

#include "iconnectroutebydisplayhint.h"

class ConnectDartsScoreRoute : public IConnectRouteByDisplayHint
{
public:
    void connectServices(AbstractRouteDartsByDisplayHint *routeService,
                         AbstractApplicationInterface *applicationService) override
    {
        QObject::connect(routeService,&AbstractRouteDartsByDisplayHint::dartsSingleColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsScoreSingleColumnInitialized);
        QObject::connect(routeService,&AbstractRouteDartsByDisplayHint::dartsMultiColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsScoreMultiColumnInitialized);
    }
};

#endif // CONNECTDARTSSCOREROUTE_H
