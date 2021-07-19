#ifndef ICONNECTROUTEBYGAMEMODE_H
#define ICONNECTROUTEBYGAMEMODE_H

#include <abstractroutebygamemode.h>
#include "abstractmodelsservice.h"
class IConnectRouteByGameMode
{
public:
    virtual void connect(AbstractModelsService *modelsService,
                         AbstractRouteByGameMode *routeByGameMode) const = 0;
};

#endif // ICONNECTROUTEBYGAMEMODE_H
