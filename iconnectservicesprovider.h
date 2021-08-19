#ifndef CONNECTSERVICEPROVIDER_H
#define CONNECTSERVICEPROVIDER_H

#include "iconnectroutebygamemode.h"
#include "iconnectroutebyinputhint.h"
#include "iconnectroutebydisplayhint.h"
#include "iconnectroutetodartsbuilder.h"
#include "iconnectdartsmodelscontext.h"
#include "iconnectplayermodelscontext.h"
#include "iconnectcontroller.h"

class IConnectServicesProvider
{
public:
    virtual IConnectRouteByGameMode *connectRouteByGameMode() const = 0;
    virtual IConnectRouteByInputHint *connectRouteByInputHint() const = 0;
    virtual IConnectRouteByDisplayHint *connectRouteByDisplayHint() const = 0;
    virtual IConnectRouteToDartsBuilder *connectDartsPointBuilder() const = 0;
    virtual IConnectRouteToDartsBuilder *connectDartsScoreBuilder() const = 0;
    virtual IConnectDartsModelsContext *connectDartsModelsContext() const = 0;
    virtual IConnectController *connectDartsPointController() const = 0;
    virtual IConnectController *connectDartsScoreController() const = 0;
    virtual IConnectPlayerModelsContext *connectPlayersContext() const = 0;
};

#endif // CONNECTSERVICEPROVIDER_H