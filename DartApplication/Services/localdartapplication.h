#ifndef LOCALDARTAPPLICATION_H
#define LOCALDARTAPPLICATION_H

#include "DartApplication/Services/dartapplication.h"
#include "DartsModelsContext/Services/dartsjsonmodelscontext.h"
#include "DartsControllerBuilder/DCBMetaServices/createDCMetaInfo.h"
#include "DartsControllerBuilder/Services/createdartscontroller.h"
#include "DartApplication/RouteServices/routeservicesprovider.h"
#include "ServicesProviderContext/SPConnectServices/connectservicesprovider.h"
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
        _dartsModelsContext = new DartsJsonModelsContext;
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
        _dcBuilder = new CreateDartsController(new CreateDPC,new CreateDSC, new CreateDCMetaInfo);
        return this;
    }
};

#endif // LOCALDARTAPPLICATION_H
