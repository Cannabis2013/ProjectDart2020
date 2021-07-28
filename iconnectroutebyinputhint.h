#ifndef ICONNECTROUTEBYINPUTHINT_H
#define ICONNECTROUTEBYINPUTHINT_H

#include "abstractdartsmodelscontext.h"
#include "abstractroutebyinputhint.h"

class IConnectRouteByInputHint
{
public:
    virtual void connectServices(AbstractDartsModelsContext* modelsService,
                                 AbstractRouteByInputHint* routeByInputHint) = 0;

};

#endif // ICONNECTROUTEBYINPUTHINT_H
