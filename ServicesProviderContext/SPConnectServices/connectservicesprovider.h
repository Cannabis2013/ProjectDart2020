#ifndef CONNECTSERVICESPROVIDER_H
#define CONNECTSERVICESPROVIDER_H

#include "ServicesProviderContext/SPConnectSLAs//iconnectservicesprovider.h"

#include "DartApplication/ConnectBuilderServices/ConnectDCBuilder.h"
#include "DartsModelsContext/DMCConnectServices/connectdartsmodelscontext.h"
#include "DartApplication/ConnectRouteServices/connectroutebyinputhint.h"
#include "DartApplication/ConnectRouteServices/connectroutebygamemode.h"
#include "PlayerModelsContext/PMCConnectServices/connectplayerscontext.h"
#include "DartsController/DCConnectServices/connectdartscontroller.h"
class ConnectServicesProvider : public IConnectServicesProvider
{
public:
    virtual IConnectRouteByGameMode *connectRouteByGameMode() const override
    {
        return _connectRouteByGameMode;
    }
    virtual IConnectRouteByInputHint *connectRouteByDisplayHint() const override
    {
        return _connectRouteByDisplayHint;
    }
    virtual IConnectDCBuilder *connectDCBuilder() const override
    {
        return _connectDCBuilder;
    }
    virtual IConnectDartsModelsContext *connectDartsModelsContext() const override
    {
        return _connectModelsServiceInterface;
    }
    virtual IConnectPlayerModelsContext *connectPlayersContext() const override
    {
        return _connectPlayersContext;
    }
    virtual IConnectController *connectDC() const override
    {
        return _connectDartsController;
    }
private:
    // Connect route services
    ConnectRouteByGameMode *_connectRouteByGameMode = new ConnectRouteByGameMode;
    ConnectRouteByInputHint *_connectRouteByDisplayHint = new ConnectRouteByInputHint;
    // Connect darts controller builder services
    ConnectDCBuilder *_connectDCBuilder = new ConnectDCBuilder;
    // Connect models interface
    ConnectDartsModelsContext *_connectModelsServiceInterface = new ConnectDartsModelsContext;
    // Connect player models interface
    ConnectPlayersContext *_connectPlayersContext = new ConnectPlayersContext;
    // Connect controller services
    IConnectController *_connectDartsController = new ConnectDartsController;
};

#endif // CONNECTSERVICESPROVIDER_H
