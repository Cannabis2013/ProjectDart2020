#ifndef ICONNECTROUTEBYDISPLAYHINT_H
#define ICONNECTROUTEBYDISPLAYHINT_H

#include "abstractroutebydisplayhint.h"
#include "AbstractApplicationInterface.h"

class IConnectRouteByDisplayHint
{
public:
    virtual void connectServices(AbstractRouteByDisplayHint* routeService,
                         AbstractApplicationInterface* applicationService) = 0;

};

#endif // ICONNECTROUTEBYDISPLAYHINT_H
