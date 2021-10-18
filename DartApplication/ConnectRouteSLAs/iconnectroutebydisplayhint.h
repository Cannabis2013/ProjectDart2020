#ifndef ICONNECTROUTEBYDISPLAYHINT_H
#define ICONNECTROUTEBYDISPLAYHINT_H

#include "DartApplication/RouteSLAs/abstractroutebyhint.h"
#include "DartApplication/SLAs/AbstractApplicationInterface.h"

class IConnectRouteByDisplayHint
{
public:
    virtual void connectServices(AbstractRouteByHint* routeService,
                                 AbstractApplicationInterface* applicationService) = 0;

};

#endif // ICONNECTROUTEBYDISPLAYHINT_H
