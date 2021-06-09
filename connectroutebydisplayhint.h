#ifndef CONNECTROUTEBYDISPLAYHINT_H
#define CONNECTROUTEBYDISPLAYHINT_H

#include "iconnectroutebydisplayhint.h"
#include <qobject.h>

class ConnectRouteByDisplayHint : public IConnectRouteByDisplayHint
{
public:
    void connectServices(AbstractRouteByDisplayHint *routeService, AbstractApplicationInterface *applicationService) override
    {
        QObject::connect(routeService,&AbstractRouteByDisplayHint::sendDartsPointSingleAttempt,
                applicationService,&AbstractApplicationInterface::setDartsPointSingleAttempt);
        QObject::connect(routeService,&AbstractRouteByDisplayHint::sendDartsScoreMultiAttempt,
                         applicationService,&AbstractApplicationInterface::setDartsScoreMultiAttempt);
    }
};

#endif // CONNECTROUTEBYDISPLAYHINT_H
