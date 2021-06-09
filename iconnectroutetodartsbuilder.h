#ifndef ICONNECTROUTE_H
#define ICONNECTROUTE_H

#include "abstractroutebyinputhint.h"
#include "abstractdartscontrollerbuilder.h"
#include "abstractroutebydisplayhint.h"

class IConnectRouteToDartsBuilder
{
public:
    virtual void connectServices(AbstractRouteByInputHint *routeByInputHint,
                                 AbstractDartsControllerBuilder *builderService,
                                 AbstractRouteByDisplayHint* routeByDisplayHint) = 0;
};


#endif // ICONNECTROUTE_H
