#ifndef LOCALDARTAPPLICATION_H
#define LOCALDARTAPPLICATION_H

#include "dartapplication.h"
#include "jsonmodelsservice.h"
#include "createDCMetaInfo.h"
#include <dartspointcontrollerbuilder.h>
#include <dartsscorebuilderservice.h>
#include "routeservicesprovider.h"
#include "connectservicesprovider.h"
#include "localplayerscontext.h"

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
                ->createDartsBuilders();
        return app;
    }

    LocalDartApplication *createDartsBuilders()
    {
        using namespace DartsBuilderContext;
        _createDartsPointController = DartsPointControllerBuilder::createInstance()
                ->setDCMetaInfoCreator(new createDCMetaInfo);
        _createDartsScoreController = DartsScoreBuilderService::createInstance()
                ->setBuildEntityByJson(new createDCMetaInfo);
        return this;
    }
};

#endif // LOCALDARTAPPLICATION_H
