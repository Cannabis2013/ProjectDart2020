#ifndef APPLICATIONBUILDER_H
#define APPLICATIONBUILDER_H

#include "connectcontrollerbuilder.h"
#include "connectdartssingleattemptpointcontroller.h"
#include "connectdartsmultiattemptcontroller.h"
#include "connectdefaultmodelscontextinterface.h"
#include "defaultmodelsservicebuilder.h"
#include "dartapplication.h"
#include "dartscontrollerbuilder.h"

class ApplicationBuilder
{
public:
    static DartApplication* createLocalDartApplicationWithJsonDb()
    {

        auto dartsControllerBuilder = DartsBuilderContext::DartsControllerBuilder::createInstance()
                ->setConnectDartsSingleAttemptPointController(new ConnectDartsSingleAttemptPointController)
                ->setConnectDartsMultiAttemptScoreController(new ConnectDartsMultiAttemptController);
        auto _dart =
                DartApplication::createInstance()
                ->setModelsServiceBuilder(DefaultModelsServiceBuilder::createInstance())
                ->setControllerBuilder(dartsControllerBuilder)
                ->setConnectModelsServiceInterface(new ConnectDefaultModelsContextInterface)
                ->setConnectControllerBuilder(new ConnectControllerBuilder)
                ->setup();
        return _dart;
    };
};

#endif // APPLICATIONBUILDER_H
