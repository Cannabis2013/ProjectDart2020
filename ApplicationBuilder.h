#ifndef APPLICATIONBUILDER_H
#define APPLICATIONBUILDER_H

#include "dartapplication.h"
#include "connectdartspointcontroller.h"
#include "connectdartsscorecontroller.h"
#include "connectdefaultmodelscontextinterface.h"
#include "defaultmodelsservicebuilder.h"
#include "dartspointbuilderservice.h"
#include "dartsscorebuilderservice.h"
#include "BuildDartsControllerEntity.h"
#include "buildsingleattemptpointcontroller.h"
#include "buildmultiattemptscorecontroller.h"
#include "routebytournamentgamemode.h"
#include "connectroutebygamemode.h"
#include "connectdartspointbuilder.h"
#include "ConnectRouteToDartsScoreBuilder.h"
#include "connectdartsscorecontroller.h"
#include "connectdartspointcontroller.h"
#include "routedartsbyinputhint.h"
#include "routedartspointbydisplayhint.h"
#include "connectroutebyinputhint.h"
#include "connectdartspointroute.h"
#include "connectdartsscoreroute.h"

class ApplicationBuilder
{
public:
    static DartApplication* createLocalDartApplicationWithJsonDb()
    {

        auto dartsPointBuilderService = DartsBuilderContext::DartsPointBuilderService::createInstance()
                ->setBuildEntityByJson(DartsBuilderContext::BuildDartsControllerEntity::createInstance())
                ->setBuildSingleAttemptPointController(new DartsBuilderContext::BuildSingleAttemptPointController);
        auto dartsScoreBuilderService = DartsBuilderContext::DartsScoreBuilderService::createInstance()
                ->setBuildEntityByJson(DartsBuilderContext::BuildDartsControllerEntity::createInstance())
                ->setBuildScoreControllerService(new DartsBuilderContext::BuildMultiAttemptScoreController);
        auto _dart =
                DartApplication::createInstance()
                ->setModelsServiceBuilder(DefaultModelsServiceBuilder::createInstance())
                ->setDartsPointBuilderService(dartsPointBuilderService)
                ->setDartsScoreControllerBuilder(dartsScoreBuilderService)
                ->setConnectModelsServiceInterface(new ConnectDefaultModelsContextInterface)
                ->setDetermineTournamentGameMode(new RouteByTournamentGameMode)
                ->setConnectRouteByGameMode(new ConnectRouteByGameMode)
                ->setConnectToDartsPountBuilder(new ConnectDartsPointBuilder)
                ->setConnectToDartsScoreBuilder(new ConnectRouteToDartsScoreBuilder)
                ->setConnectDartsPointController(new ConnectDartsPointController)
                ->setConnectDartsScoreController(new ConnectDartsScoreController)
                ->setRouteByInputHint(new RouteDartsByInputHint)
                ->setRouteByDisplayHint(new RouteDartsPointByDisplayHint)
                ->setConnectRouteByInputHint(new ConnectRouteByInputHint)
                ->setConnectDartsPointRoute(new ConnectDartsPointRoute)
                ->setConnectDartsScoreRoute(new ConnectDartsScoreRoute)
                ->setup();
        return _dart;
    };
};

#endif // APPLICATIONBUILDER_H
