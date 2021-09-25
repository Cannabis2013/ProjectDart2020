#ifndef ICONNECTROUTEBYDISPLAYHINT_H
#define ICONNECTROUTEBYDISPLAYHINT_H

#include "DartApplication/RouteSLAs/abstractroutebydisplayhint.h"
#include "DartApplication/SLAs/AbstractApplicationInterface.h"

class IConnectRouteByDisplayHint
{
public:
    virtual void connectServices(AbstractRouteByDisplayHint* routeService,
                                 AbstractApplicationInterface* applicationService) = 0;

};

#endif // ICONNECTROUTEBYDISPLAYHINT_H
