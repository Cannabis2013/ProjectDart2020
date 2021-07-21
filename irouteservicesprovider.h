#ifndef IROUTESERVICESPROVIDER_H
#define IROUTESERVICESPROVIDER_H

#include "abstractroutebygamemode.h"
#include "abstractroutebyinputhint.h"
#include "abstractroutebydisplayhint.h"

#include <routebydisplayhint.h>
#include <routebytournamentgamemode.h>
#include <routedartsbyinputhint.h>

class IRouteServicesProvider
{
public:
    virtual AbstractRouteByGameMode *routeByGameMode() const = 0;
    virtual AbstractRouteByInputHint *routeByInputHint() const  = 0;
    virtual AbstractRouteByDisplayHint *routeByDisplayHint() const  = 0;
};

#endif // IROUTESERVICEPROVIDER_H
