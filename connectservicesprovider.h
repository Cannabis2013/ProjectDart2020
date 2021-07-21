#ifndef CONNECTSERVICESPROVIDER_H
#define CONNECTSERVICESPROVIDER_H

#include "iconnectservicesprovider.h"

#include <ConnectDartsScoreBuilder.h>
#include <connectdartspointbuilder.h>
#include <connectdefaultmodelscontextinterface.h>
#include <connectroutebydisplayhint.h>
#include <connectroutebygamemode.h>
#include <connectroutebyinputhint.h>
#include "connectdartspointcontroller.h"
#include "connectdartsscorecontroller.h"
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
    virtual IConnectModelsInterface *connectModelsServiceInterface() const override
    {
        return _connectModelsServiceInterface;
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
    ConnectDefaultModelsContextInterface *_connectModelsServiceInterface = new ConnectDefaultModelsContextInterface;
    // Connect controller services
    IConnectController *_connectDartsPointController = new ConnectDartsPointController;
    IConnectController *_connectDartsScoreController = new ConnectDartsScoreController;
};

#endif // CONNECTSERVICESPROVIDER_H
