#ifndef CONNECTDARTSPOINTROUTE_H
#define CONNECTDARTSPOINTROUTE_H

#include "DartApplication/ConnectRouteSLAs/iconnectroutebydisplayhint.h"

class ConnectRouteByDisplayHint : public IConnectRouteByDisplayHint
{
public:
    void connectServices(AbstractRouteByHint *routeService,
                         AbstractApplicationInterface *applicationService) override
    {
        connectPointControllers(routeService,applicationService);
        connectScoreControllers(routeService,applicationService);
    }

private:
    void connectPointControllers(AbstractRouteByHint *routeService,
                                 AbstractApplicationInterface *applicationService)
    {
        QObject::connect(routeService,&AbstractRouteByHint::dartsPointSingleColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsPointSingleColumnInitialized);
        QObject::connect(routeService,&AbstractRouteByHint::dartsPointMultiColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsPointMultiColumnsInitialized);
    }
    void connectScoreControllers(AbstractRouteByHint *routeService,
                                 AbstractApplicationInterface *applicationService)
    {
        QObject::connect(routeService,&AbstractRouteByHint::dartsScoreSingleColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsScoreSingleColumnInitialized);
        QObject::connect(routeService,&AbstractRouteByHint::dartsScoreMultiColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsScoreMultiColumnInitialized);
    }
};

#endif // CONNECTRDARTSPOINTROUTE_H
