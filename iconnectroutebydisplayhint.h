#ifndef ICONNECTROUTEBYDISPLAYHINT_H
#define ICONNECTROUTEBYDISPLAYHINT_H

#include "abstractroutedartsbydisplayhint.h"
#include "AbstractApplicationInterface.h"

class IConnectRouteByDisplayHint
{
public:
    virtual void connectServices(AbstractRouteDartsByDisplayHint* routeService,
                                 AbstractApplicationInterface* applicationService) = 0;

};

#endif // ICONNECTROUTEBYDISPLAYHINT_H
