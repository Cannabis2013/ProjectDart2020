#ifndef APPLICATIONBUILDER_H
#define APPLICATIONBUILDER_H

#include "connectcontrollerbuilder.h"
#include "connectdartssingleattemptpointcontroller.h"
#include "connectdartsmultiattemptcontroller.h"
#include "connectdefaultmodelscontextinterface.h"
#include "defaultmodelsservicebuilder.h"
#include "dartapplication.h"
#include "dartscontrollerbuilder.h"
#include "BuildDartsControllerEntity.h"
#include "buildsingleattemptpointcontroller.h"
#include "buildmultiattemptscorecontroller.h"
#include "determinetournamentgamemode.h"
#include "connecttournamentgamemodeservice.h"

class ApplicationBuilder
{
public:
    static DartApplication* createLocalDartApplicationWithJsonDb()
    {

        auto dartsControllerBuilder = DartsBuilderContext::DartsControllerBuilder::createInstance()
                ->setConnectDartsSingleAttemptPointController(new ConnectDartsSingleAttemptPointController)
                ->setConnectDartsMultiAttemptScoreController(new ConnectDartsMultiAttemptController)
                ->setBuildEntityByJson(DartsBuilderContext::BuildDartsControllerEntity::createInstance())
                ->setBuildSingleAttemptPointController(new DartsBuilderContext::BuildSingleAttemptPointController)
                ->setBuildMultiAttemptScoreController(new BuildMultiAttemptScoreController);
        auto _dart =
                DartApplication::createInstance()
                ->setModelsServiceBuilder(DefaultModelsServiceBuilder::createInstance())
                ->setControllerBuilder(dartsControllerBuilder)
                ->setConnectModelsServiceInterface(new ConnectDefaultModelsContextInterface)
                ->setConnectControllerBuilder(new ConnectControllerBuilder)
                ->setDetermineTournamentGameMode(new DetermineTournamentGameMode)
                ->setConnectTournamentGameModeService(new ConnectTournamentGameModeService)
                ->setup();
        return _dart;
    };
};

#endif // APPLICATIONBUILDER_H
