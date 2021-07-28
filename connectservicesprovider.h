#ifndef CONNECTSERVICESPROVIDER_H
#define CONNECTSERVICESPROVIDER_H

#include "iconnectservicesprovider.h"

#include <ConnectDartsScoreBuilder.h>
#include <connectdartspointbuilder.h>
#include <connectdartsmodelscontext.h>
#include <connectroutebydisplayhint.h>
#include <connectroutebygamemode.h>
#include <connectroutebyinputhint.h>
#include <connectplayerscontext.h>
#include "connectdartspointcontroller.h"
#include "connectdartsscorecontroller.h"
#include "connectplayerscontext.h"
class ConnectServicesProvider : public IConnectServicesProvider
{
public:
    virtual IConnectRouteByGameMode *connectRouteByGameMode() const override
    {
        return _connectRouteByGameMode;
    }
    virtual IConnectRouteByInputHint *connectRouteByInputHint() const override
    {
        return _connectRouteByInputHint;
    }
    virtual IConnectRouteByDisplayHint *connectRouteByDisplayHint() const override
    {
        return _connectRouteByDisplayHint;
    }
    virtual IConnectRouteToDartsBuilder *connectDartsPointBuilder() const override
    {
        return _connectDartsPointBuilder;
    }
    virtual IConnectRouteToDartsBuilder *connectDartsScoreBuilder() const override
    {
        return _connectDartsScoreBuilder;
    }
    virtual IConnectDartsModelsContext *connectDartsModelsContext() const override
    {
        return _connectModelsServiceInterface;
    }
    virtual IConnectPlayerModelsContext *connectPlayersContext() const override
    {
        return _connectPlayersContext;
    }
    virtual IConnectController *connectDartsPointController() const override
    {
        return _connectDartsPointController;
    }
    virtual IConnectController *connectDartsScoreController() const override
    {
        return _connectDartsScoreController;
    }
private:
    // Connect route services
    ConnectRouteByGameMode *_connectRouteByGameMode = new ConnectRouteByGameMode;
    ConnectRouteByInputHint *_connectRouteByInputHint = new ConnectRouteByInputHint;
    ConnectRouteByDisplayHint *_connectRouteByDisplayHint = new ConnectRouteByDisplayHint;
    // Connect darts controller builder services
    ConnectDartsPointBuilder *_connectDartsPointBuilder = new ConnectDartsPointBuilder;
    ConnectDartsScoreBuilder *_connectDartsScoreBuilder = new ConnectDartsScoreBuilder;
    // Connect models interface
    ConnectDartsModelsContext *_connectModelsServiceInterface = new ConnectDartsModelsContext;
    // Connect player models interface
    ConnectPlayersContext *_connectPlayersContext = new ConnectPlayersContext;
    // Connect controller services
    IConnectController *_connectDartsPointController = new ConnectDartsPointController;
    IConnectController *_connectDartsScoreController = new ConnectDartsScoreController;
};

#endif // CONNECTSERVICESPROVIDER_H
