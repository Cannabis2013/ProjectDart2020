#ifndef CONNECTDARTSPOINTROUTE_H
#define CONNECTDARTSPOINTROUTE_H

#include "iconnectroutebydisplayhint.h"

class ConnectDartsPointRoute : public IConnectRouteByDisplayHint
{
public:
    void connectServices(AbstractRouteDartsByDisplayHint *routeService,
                         AbstractApplicationInterface *applicationService) override
    {
        QObject::connect(routeService,&AbstractRouteDartsByDisplayHint::dartsSingleColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsPointSingleColumnInitialized);
        QObject::connect(routeService,&AbstractRouteDartsByDisplayHint::dartsMultiColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsPointMultiColumnsInitialized);
    }
};

#endif // CONNECTRDARTSPOINTROUTE_H
