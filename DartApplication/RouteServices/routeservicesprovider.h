#ifndef ROUTESERVICESPROVIDER_H
#define ROUTESERVICESPROVIDER_H

#include "DartApplication/RouteSLAs/irouteservicesprovider.h"
#include "DartApplication/RouteServices/routebydisplayhint.h"
#include "DartApplication/RouteServices/routebytournamentgamemode.h"
class RouteServicesProvider : public IRouteServicesProvider
{
public:
    RouteByTournamentGameMode *routeByGameMode() const override
    {
        return _routeTournamentByGameMode;
    }
    RouteByDisplayHint *routeByDisplayHint() const override
    {
        return _routeDartsControllerByDisplayHint;
    }
private:
    RouteByTournamentGameMode *_routeTournamentByGameMode = new RouteByTournamentGameMode;
    RouteByDisplayHint *_routeDartsControllerByDisplayHint = new RouteByDisplayHint;
};

#endif // ROUTESERVICESPROVIDER_H
