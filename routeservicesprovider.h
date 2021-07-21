#ifndef ROUTESERVICESPROVIDER_H
#define ROUTESERVICESPROVIDER_H

#include "irouteservicesprovider.h"
class RouteServicesProvider : public IRouteServicesProvider
{
public:
    RouteByTournamentGameMode *routeByGameMode() const override
    {
        return _routeTournamentByGameMode;
    }
    RouteDartsByInputHint *routeByInputHint() const override
    {
        return _routeDartsControllerByInputHint;
    }
    RouteByDisplayHint *routeByDisplayHint() const override
    {
        return _routeDartsControllerByDisplayHint;
    }
private:
    RouteByTournamentGameMode *_routeTournamentByGameMode = new RouteByTournamentGameMode;
    RouteDartsByInputHint *_routeDartsControllerByInputHint = new RouteDartsByInputHint;
    RouteByDisplayHint *_routeDartsControllerByDisplayHint = new RouteByDisplayHint;
};

#endif // ROUTESERVICESPROVIDER_H
