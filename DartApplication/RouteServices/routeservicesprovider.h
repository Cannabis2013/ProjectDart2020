#ifndef ROUTESERVICESPROVIDER_H
#define ROUTESERVICESPROVIDER_H

#include "DartApplication/RouteSLAs/irouteservicesprovider.h"
#include "DartApplication/RouteServices/routebyinputhint.h"
#include "DartApplication/RouteServices/routebytournamentgamemode.h"
class RouteServicesProvider : public IRouteServicesProvider
{
public:
    RouteByTournamentGameMode *routeByGameMode() const override
    {
        return _routeTournamentByGameMode;
    }
    RouteByInputHint *routeByInputHint() const override
    {
        return _routeByInputHint;
    }
private:
    RouteByTournamentGameMode *_routeTournamentByGameMode = new RouteByTournamentGameMode;
    RouteByInputHint *_routeByInputHint = new RouteByInputHint;
};

#endif // ROUTESERVICESPROVIDER_H
