#ifndef LOCALDARTAPPLICATION_H
#define LOCALDARTAPPLICATION_H

#include "dartapplication.h"
#include "jsonmodelsservice.h"
#include "createDCMetaInfo.h"
#include <createdartscontroller.h>
#include "routeservicesprovider.h"
#include "connectservicesprovider.h"
#include "PlayerModelsContext/localplayerscontext.h"

class LocalDartApplication : public DartApplication
{
public:
    LocalDartApplication()
    {
        // Route services provider
        _routeServices = new RouteServicesProvider;
        // Connect service provider
        _connectServices = new ConnectServicesProvider;
        // Darts models service
        _dartsModelsContext = new JsonModelsService;
        // Player models context
        _playerModelsContext = new LocalPlayersContext;
    }
    static LocalDartApplication *createInstance()
    {
        return new LocalDartApplication();
    }

    static LocalDartApplication *createAndSetupInstance()
    {
        auto app = LocalDartApplication::createInstance()
                ->createDCBuilder();
        return app;
    }

    LocalDartApplication *createDCBuilder()
    {
        _dcBuilder = new CreateDartsController();
        return this;
    }
};

#endif // LOCALDARTAPPLICATION_H
