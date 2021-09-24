#ifndef ICONNECTROUTEBYGAMEMODE_H
#define ICONNECTROUTEBYGAMEMODE_H

#include <abstractroutebygamemode.h>
#include "DartsModelsContext/abstractdartsmodelscontext.h"
class IConnectRouteByGameMode
{
public:
    virtual void connect(AbstractDartsModelsContext *modelsService,
                         AbstractRouteByGameMode *routeByGameMode) const = 0;
};

#endif // ICONNECTROUTEBYGAMEMODE_H
