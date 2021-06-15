#ifndef CONNECTDARTSPOINTROUTE_H
#define CONNECTDARTSPOINTROUTE_H

#include "iconnectroutebydisplayhint.h"

class ConnectRouteByDisplayHint : public IConnectRouteByDisplayHint
{
public:
    void connectServices(AbstractRouteDartsByDisplayHint *routeService,
                         AbstractApplicationInterface *applicationService) override
    {
        connectPointControllers(routeService,applicationService);
        connectScoreControllers(routeService,applicationService);
    }

private:
    void connectPointControllers(AbstractRouteDartsByDisplayHint *routeService,
                                 AbstractApplicationInterface *applicationService)
    {
        QObject::connect(routeService,&AbstractRouteDartsByDisplayHint::dartsPointSingleColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsPointSingleColumnInitialized);
        QObject::connect(routeService,&AbstractRouteDartsByDisplayHint::dartsPointMultiColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsPointMultiColumnsInitialized);
    }
    void connectScoreControllers(AbstractRouteDartsByDisplayHint *routeService,
                                 AbstractApplicationInterface *applicationService)
    {
        QObject::connect(routeService,&AbstractRouteDartsByDisplayHint::dartsScoreSingleColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsScoreSingleColumnInitialized);
        QObject::connect(routeService,&AbstractRouteDartsByDisplayHint::dartsScoreMultiColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsScoreMultiColumnInitialized);
    }
};

#endif // CONNECTRDARTSPOINTROUTE_H
