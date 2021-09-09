#ifndef IROUTESERVICESPROVIDER_H
#define IROUTESERVICESPROVIDER_H

#include "abstractroutebygamemode.h"
#include "abstractroutebydisplayhint.h"

class IRouteServicesProvider
{
public:
    virtual AbstractRouteByGameMode *routeByGameMode() const = 0;
    virtual AbstractRouteByDisplayHint *routeByDisplayHint() const  = 0;
};

#endif // IROUTESERVICEPROVIDER_H
