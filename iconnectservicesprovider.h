#ifndef CONNECTSERVICEPROVIDER_H
#define CONNECTSERVICEPROVIDER_H

#include "iconnectroutebygamemode.h"
#include "iconnectroutebydisplayhint.h"
#include "iconnectdartsmodelscontext.h"
#include "iconnectplayermodelscontext.h"
#include "iconnectcontroller.h"

#include <iconnectdcbuilder.h>

class IConnectServicesProvider
{
public:
    virtual IConnectRouteByGameMode *connectRouteByGameMode() const = 0;
    virtual IConnectRouteByDisplayHint *connectRouteByDisplayHint() const = 0;
    virtual IConnectDCBuilder *connectDCBuilder() const = 0;
    virtual IConnectDartsModelsContext *connectDartsModelsContext() const = 0;
    virtual IConnectController *connectDartsController() const = 0;
    virtual IConnectPlayerModelsContext *connectPlayersContext() const = 0;
};

#endif // CONNECTSERVICEPROVIDER_H
