#ifndef IROUTESERVICESPROVIDER_H
#define IROUTESERVICESPROVIDER_H

#include "DartApplication/RouteSLAs/abstractroutebygamemode.h"
#include "DartApplication/RouteSLAs/abstractroutebyhint.h"

class IRouteServicesProvider
{
public:
    virtual AbstractRouteByGameMode *routeByGameMode() const = 0;
    virtual AbstractRouteByHint *routeByInputHint() const  = 0;
};

#endif // IROUTESERVICEPROVIDER_H
