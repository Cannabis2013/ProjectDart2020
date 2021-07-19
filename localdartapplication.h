#ifndef LOCALDARTAPPLICATION_H
#define LOCALDARTAPPLICATION_H

#include "dartapplication.h"

#include <ConnectDartsScoreBuilder.h>
#include <connectdartspointbuilder.h>
#include <connectdartspointcontroller.h>
#include <connectdartsscorecontroller.h>
#include <connectdefaultmodelscontextinterface.h>
#include <connectroutebydisplayhint.h>
#include <connectroutebygamemode.h>
#include <connectroutebyinputhint.h>
#include <routebydisplayhint.h>
#include <routebytournamentgamemode.h>
#include <routedartsbyinputhint.h>
#include "jsondartsmodelsservice.h"

#include <dartspointcontrollerbuilder.h>
#include <dartsscorebuilderservice.h>

class LocalDartApplication : public DartApplication
{
public:
    LocalDartApplication()
    {
        // Route services
        _routeTournamentByGameMode = new RouteByTournamentGameMode;
         _routeDartsControllerByInputHint = new RouteDartsByInputHint;
        _routeDartsControllerByDisplayHint = new RouteByDisplayHint;
        // Connect route services
        _connectRouteByGameMode = new ConnectRouteByGameMode();
        _connectRouteByInputHint = new ConnectRouteByInputHint;;
        _connectRouteByDisplayHint = new ConnectRouteByDisplayHint;
        // Connect darts controller services
        _connectDartsPointBuilder = new ConnectDartsPointBuilder;
        _connectDartsScoreBuilder = new ConnectDartsScoreBuilder;
        _connectDartsPointController = new ConnectDartsPointController;
        _connectDartsScoreController = new ConnectDartsScoreController;
        _connectModelsServiceInterface = new ConnectDefaultModelsContextInterface;
        // Set models service
        _modelsService = new JsonDartsModelsService;
    }

    static LocalDartApplication *createInstance()
    {
        return new LocalDartApplication();
    }

    static LocalDartApplication *createAndSetupInstance()
    {
        auto app = LocalDartApplication::createInstance()
                ->createDartsBuilders()
                ->registerTypes()
                ->connectServices();
        return app;
    }

    LocalDartApplication *createDartsBuilders()
    {
        using namespace DartsBuilderContext;
        _dartsPointBuilder = DartsPointControllerBuilder::createInstance()
                ->setBuildEntityByJson(BuildDartsControllerEntity::createInstance());
        _dartsScoreBuilder = DartsScoreBuilderService::createInstance()
                ->setBuildEntityByJson(BuildDartsControllerEntity::createInstance());
        return this;
    }

    LocalDartApplication *connectServices()
    {
        _connectRouteByGameMode->connect(_modelsService,_routeTournamentByGameMode);
        _connectModelsServiceInterface->connect(this,_modelsService);
        _connectRouteByInputHint->connectServices(_modelsService,_routeDartsControllerByInputHint);
        /*
         * Connect darts builder services
         */
        _connectDartsPointBuilder->connectServices(_routeDartsControllerByInputHint,_dartsPointBuilder,this);
        _connectDartsScoreBuilder->connectServices(_routeDartsControllerByInputHint,_dartsScoreBuilder,this);
        /*
         * Connect route from the point where controllers are initialized to the route interface
         */
        _connectRouteByDisplayHint->connectServices(_routeDartsControllerByDisplayHint,this);
        return this;
    }
    LocalDartApplication *registerTypes()
    {
        qRegisterMetaType<QByteArray>("QByteArray");
        qRegisterMetaType<AbstractApplicationInterface*>("AbstractApplicationInterface");
        qRegisterMetaType<AbstractModelsService*>("AbstractModelsService");
        qRegisterMetaType<AbstractGameController*>("AbstractGameController");
        qRegisterMetaType<AbstractDartsController*>("AbstractDartsController");
        return this;
    }
};

#endif // LOCALDARTAPPLICATION_H
