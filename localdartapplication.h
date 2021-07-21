#ifndef LOCALDARTAPPLICATION_H
#define LOCALDARTAPPLICATION_H

#include "dartapplication.h"

#include "jsonmodelsservice.h"
#include <dartspointcontrollerbuilder.h>
#include <dartsscorebuilderservice.h>
#include "routeservicesprovider.h"
#include "connectservicesprovider.h"

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
        _modelsService = new JsonModelsService;
    }

    static LocalDartApplication *createInstance()
    {
        return new LocalDartApplication();
    }

    static LocalDartApplication *createAndSetupInstance()
    {
        auto app = LocalDartApplication::createInstance()
                ->createDartsBuilders();
        return app;
    }

    LocalDartApplication *createDartsBuilders()
    {
        using namespace DartsBuilderContext;
        _createDartsPointController = DartsPointControllerBuilder::createInstance()
                ->setBuildEntityByJson(BuildDartsControllerEntity::createInstance());
        _createDartsScoreController = DartsScoreBuilderService::createInstance()
                ->setBuildEntityByJson(BuildDartsControllerEntity::createInstance());
        return this;
    }
};

#endif // LOCALDARTAPPLICATION_H
