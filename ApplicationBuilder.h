#ifndef APPLICATIONBUILDER_H
#define APPLICATIONBUILDER_H

#include "connectdartssingleattemptpointcontroller.h"
#include "defaultmodelsservicebuilder.h"
#include "dartsmodelsservicebuilder.h"
#include "playermodelsservicebuilder.h"
#include "connectdefaultmodelscontextinterface.h"
#include "connectcontrollerbuilder.h"
#include "dartsjsonservicebuilder.h"
#include "dartapplication.h"
#include "dartscontrollerbuilder.h"
#include "connectdartsmultiattemptcontroller.h"

class ApplicationBuilder
{
public:
    static DartApplication* createLocalDartApplicationWithJsonDb()
    {

        auto dartsControllerBuilder = DartsControllerBuilder::createInstance()
                ->setConnectDartsSingleAttemptPointController(new ConnectDartsSingleAttemptPointController)
                ->setConnectDartsMultiAttemptScoreController(new ConnectDartsMultiAttemptController);

        auto modelsServiceBuilder = DefaultModelsServiceBuilder::createInstance()
                ->setModelsTournamentServiceBuilder(new DartsModelsServiceBuilder)
                ->setPlayerServiceBuilder(new PlayerModelsServiceBuilder)
                ->setDartsJSonServiceBuilder(new DartsJsonServiceBuilder);

        auto _dart =
                DartApplication::createInstance()
                ->setModelsServiceBuilder(modelsServiceBuilder)
                ->setControllerBuilder(dartsControllerBuilder)
                ->setConnectModelsServiceInterface(new ConnectDefaultModelsContextInterface)
                ->setConnectControllerBuilder(new ConnectControllerBuilder)
                ->setup();
        return _dart;
    };
};

#endif // APPLICATIONBUILDER_H
