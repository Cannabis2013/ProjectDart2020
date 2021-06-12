#ifndef ICONNECTROUTE_H
#define ICONNECTROUTE_H

#include "abstractroutebyinputhint.h"
#include "abstractdartscontrollerbuilder.h"
#include "AbstractApplicationInterface.h"

class IConnectRouteToDartsBuilder
{
public:
    virtual void connectServices(AbstractRouteByInputHint *routeByInputHint,
                                 AbstractDartsControllerBuilder *builderService,
                                 AbstractApplicationInterface* applicationService) = 0;
};


#endif // ICONNECTROUTE_H
