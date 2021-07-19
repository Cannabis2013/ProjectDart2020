#ifndef DARTAPPLICATIONSERVICES_H
#define DARTAPPLICATIONSERVICES_H

#include <abstractdartscontrollerbuilder.h>
#include <abstractroutebyinputhint.h>
#include <abstractroutedartsbydisplayhint.h>
#include <iconnectdartspointcontroller.h>
#include <iconnectdartsscorecontroller.h>
#include <iconnectmodelsinterface.h>
#include <iconnectroutebydisplayhint.h>
#include <iconnectroutebyinputhint.h>
#include <iconnectroutetodartsbuilder.h>
#include "iconnectroutebygamemode.h"

inline IConnectRouteByGameMode *DartRouteServiceProvider::connectRouteByGameMode() const
{
    return _connectRouteByGameMode;
}

inline void DartRouteServiceProvider::setConnectRouteByGameMode(IConnectRouteByGameMode *newConnectRouteByGameMode)
{
    _connectRouteByGameMode = newConnectRouteByGameMode;
}

inline IConnectRouteByInputHint *DartRouteServiceProvider::connectRouteByInputHint() const
{
    return _connectRouteByInputHint;
}

inline void DartRouteServiceProvider::setConnectRouteByInputHint(IConnectRouteByInputHint *newConnectRouteByInputHint)
{
    _connectRouteByInputHint = newConnectRouteByInputHint;
}

inline IConnectRouteByDisplayHint *DartRouteServiceProvider::connectRouteByDisplayHint() const
{
    return _connectRouteByDisplayHint;
}

inline void DartRouteServiceProvider::setConnectRouteByDisplayHint(IConnectRouteByDisplayHint *newConnectRouteByDisplayHint)
{
    _connectRouteByDisplayHint = newConnectRouteByDisplayHint;
}

class DartApplicationServices
{
protected:
    // Builders
    AbstractDartsControllerBuilder *_dartsPointBuilder;
    AbstractDartsControllerBuilder *_dartsScoreBuilder;
    // Route services
    AbstractRouteByGameMode* _routeTournamentByGameMode;
    AbstractRouteByInputHint* _routeDartsControllerByInputHint;
    AbstractRouteDartsByDisplayHint* _routeDartsControllerByDisplayHint;
    // Connect route services
    IConnectRouteByGameMode *_connectRouteByGameMode;
    IConnectRouteByInputHint *_connectRouteByInputHint;
    IConnectRouteByDisplayHint *_connectRouteByDisplayHint;
    // Connect darts controller services
    IConnectRouteToDartsBuilder *_connectDartsPointBuilder;
    IConnectRouteToDartsBuilder *_connectDartsScoreBuilder;
    IConnectDartsPointController* _connectDartsPointController;
    IConnectDartsScoreController* _connectDartsScoreController;
    IConnectModelsInterface* _connectModelsServiceInterface;
};

#endif // DARTAPPLICATIONSERVICES_H
