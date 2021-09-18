#ifndef CONNECTSERVICES_H
#define CONNECTSERVICES_H

#include "dartapplication.h"
#include "iconnectservicesprovider.h"
#include "irouteservicesprovider.h"
class ConnectServices
{
public:
    ConnectServices()
    {
        qRegisterMetaType<QByteArray>("QByteArray");
        qRegisterMetaType<AbstractApplicationInterface*>("AbstractApplicationInterface");
        qRegisterMetaType<AbstractDartsModelsContext*>("AbstractModelsService");
        qRegisterMetaType<AbstractGameController*>("AbstractGameController");
        qRegisterMetaType<AbstractDartsController*>("AbstractDartsController");
    }
    void connect(DartApplication *application,
                         const IRouteServicesProvider *routeProvider,
                         const IConnectServicesProvider *connectProvider)
    {

        connectProvider->connectRouteByGameMode()->connect(application->modelsService(),routeProvider->routeByGameMode());
        connectProvider->connectDartsModelsContext()->connect(application,application->modelsService(),application->dcBuilder());
        // Connect darts builder services
        connectProvider->connectDCBuilder()->connectServices(application->dcBuilder(),application);
        // Connect route from the point where controllers are initialized to the route interface
        connectProvider->connectRouteByDisplayHint()->connectServices(routeProvider->routeByDisplayHint(),
                                                                      application);
        // Connect players context with application
        connectProvider->connectPlayersContext()->connectServices(application,application->playerModelsContext());
    }
};

#endif // CONNECTSERVICES_H
