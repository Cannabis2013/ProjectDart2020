#ifndef ICONNECTROUTEBYINPUTHINT_H
#define ICONNECTROUTEBYINPUTHINT_H

#include "abstractmodelsservice.h"
#include "abstractroutebyinputhint.h"

class IConnectRouteByInputHint
{
public:
    virtual void connectServices(AbstractModelsService* modelsService,
                                 AbstractRouteByInputHint* routeByInputHint) = 0;

};

#endif // ICONNECTROUTEBYINPUTHINT_H
