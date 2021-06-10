#ifndef APPLICATIONBUILDER_H
#define APPLICATIONBUILDER_H

#include "connectdartssingleattemptpointcontroller.h"
#include "connectdartsscorecontroller.h"
#include "connectdefaultmodelscontextinterface.h"
#include "defaultmodelsservicebuilder.h"
#include "dartapplication.h"
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
#include "connectdartssingleattemptpointcontroller.h"
#include "routedartsbyinputhint.h"
#include "routedartsbydisplayhint.h"
#include "connectroutebyinputhint.h"
#include "connectroutebydisplayhint.h"

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
                ->setBuildMultiAttemptScoreController(new DartsBuilderContext::BuildMultiAttemptScoreController);
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
                ->setConnectDartsPointController(new ConnectDartsSingleAttemptPointController)
                ->setConnectDartsScoreController(new ConnectDartsScoreController)
                ->setRouteByInputHint(new RouteDartsByInputHint)
                ->setRouteByDisplayHint(new RouteDartsByDisplayHint)
                ->setConnectRouteByInputHint(new ConnectRouteByInputHint)
                ->setConnectRouteByDisplayHint(new ConnectRouteByDisplayHint)
                ->setup();
        return _dart;
    };
};

#endif // APPLICATIONBUILDER_H
