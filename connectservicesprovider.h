#ifndef CONNECTSERVICESPROVIDER_H
#define CONNECTSERVICESPROVIDER_H

#include "iconnectservicesprovider.h"

#include <ConnectDCBuilder.h>
#include <connectdartsmodelscontext.h>
#include <connectroutebydisplayhint.h>
#include <connectroutebygamemode.h>
#include <connectplayerscontext.h>
#include "connectdartscontroller.h"
#include "connectplayerscontext.h"
class ConnectServicesProvider : public IConnectServicesProvider
{
public:
    virtual IConnectRouteByGameMode *connectRouteByGameMode() const override
    {
        return _connectRouteByGameMode;
    }
    virtual IConnectRouteByDisplayHint *connectRouteByDisplayHint() const override
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
    virtual IConnectController *connectDartsController() const override
    {
        return _connectDartsController;
    }
private:
    // Connect route services
    ConnectRouteByGameMode *_connectRouteByGameMode = new ConnectRouteByGameMode;
    ConnectRouteByDisplayHint *_connectRouteByDisplayHint = new ConnectRouteByDisplayHint;
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
