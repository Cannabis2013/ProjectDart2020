#ifndef CONNECTDARTSPOINTROUTE_H
#define CONNECTDARTSPOINTROUTE_H

#include "DartApplication/ConnectRouteSLAs/iconnectroutebydisplayhint.h"

class ConnectRouteByDisplayHint : public IConnectRouteByDisplayHint
{
public:
    void connectServices(AbstractRouteByDisplayHint *routeService,
                         AbstractApplicationInterface *applicationService) override
    {
        connectPointControllers(routeService,applicationService);
        connectScoreControllers(routeService,applicationService);
    }

private:
    void connectPointControllers(AbstractRouteByDisplayHint *routeService,
                                 AbstractApplicationInterface *applicationService)
    {
        QObject::connect(routeService,&AbstractRouteByDisplayHint::dartsPointSingleColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsPointSingleColumnInitialized);
        QObject::connect(routeService,&AbstractRouteByDisplayHint::dartsPointMultiColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsPointMultiColumnsInitialized);
    }
    void connectScoreControllers(AbstractRouteByDisplayHint *routeService,
                                 AbstractApplicationInterface *applicationService)
    {
        QObject::connect(routeService,&AbstractRouteByDisplayHint::dartsScoreSingleColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsScoreSingleColumnInitialized);
        QObject::connect(routeService,&AbstractRouteByDisplayHint::dartsScoreMultiColumnInitialized,
                         applicationService,&AbstractApplicationInterface::dartsScoreMultiColumnInitialized);
    }
};

#endif // CONNECTRDARTSPOINTROUTE_H
