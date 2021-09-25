#ifndef CONNECTSERVICEPROVIDER_H
#define CONNECTSERVICEPROVIDER_H

#include "DartApplication/ConnectRouteSLAs/iconnectroutebygamemode.h"
#include "DartApplication/ConnectRouteSLAs/iconnectroutebydisplayhint.h"
#include "DartsModelsContext/DMCConnectSLAs/iconnectdartsmodelscontext.h"
#include "PlayerModelsContext/PMCConnectSLAs/iconnectplayermodelscontext.h"
#include "DartControllerContext/ConnectSLAs/iconnectcontroller.h"

#include "DartApplication/ConnectBuilderSLAs/iconnectdcbuilder.h"

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
