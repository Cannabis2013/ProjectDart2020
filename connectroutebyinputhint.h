#ifndef CONNECTROUTEBYINPUTHINT_H
#define CONNECTROUTEBYINPUTHINT_H

#include "iconnectroutebyinputhint.h"

class ConnectRouteByInputHint : public IConnectRouteByInputHint
{
public:
    void connectServices(AbstractDartsModelsContext* modelsService,
                 AbstractRouteByInputHint* routeByInputHint) override
    {
        QObject::connect(modelsService,&AbstractDartsModelsContext::sendDartsDetails,
                         routeByInputHint,&AbstractRouteByInputHint::processTournamentDetails);
    }
};

#endif // CONNECTROUTEBYINPUTHINT_H
