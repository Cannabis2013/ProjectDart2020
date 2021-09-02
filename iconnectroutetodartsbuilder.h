#ifndef ICONNECTROUTE_H
#define ICONNECTROUTE_H

#include "abstractroutebyinputhint.h"
#include "abstractdcbuilder.h"
#include "AbstractApplicationInterface.h"

class IConnectRouteToDartsBuilder
{
public:
    virtual void connectServices(AbstractRouteByInputHint *routeByInputHint,
                                 AbstractDCBuilder *builderService,
                                 AbstractApplicationInterface* applicationService) = 0;
};


#endif // ICONNECTROUTE_H
