#ifndef CONNECTDARTSPOINTROUTE_H
#define CONNECTDARTSPOINTROUTE_H
#include "DartApplication/ConnectRouteSLAs/iconnectroutebyinputhint.h"
class ConnectRouteByInputHint : public IConnectRouteByInputHint
{
public:
    void connectServices(AbstractRouteByHint *routeService,
                         AbstractApplicationInterface *applicationService) override
    {
        QObject::connect(routeService,&AbstractRouteByHint::dartsPointInit,
                         applicationService,&AbstractApplicationInterface::dartsPointSingleColumnInitialized);
        QObject::connect(routeService,&AbstractRouteByHint::dartsScoreInit,
                         applicationService,&AbstractApplicationInterface::dartsScoreSingleColumnInitialized);
    }
};
#endif // CONNECTRDARTSPOINTROUTE_H
