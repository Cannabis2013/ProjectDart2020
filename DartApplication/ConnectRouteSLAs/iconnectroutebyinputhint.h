#ifndef ICONNECTROUTEBYINPUTHINT_H
#define ICONNECTROUTEBYINPUTHINT_H

#include "DartApplication/RouteSLAs/abstractroutebyhint.h"
#include "DartApplication/SLAs/AbstractApplicationInterface.h"

class IConnectRouteByInputHint
{
public:
    virtual void connectServices(AbstractRouteByHint* routeService,
                                 AbstractApplicationInterface* applicationService) = 0;

};

#endif // ICONNECTROUTEBYINPUTHINT_H
