#include "dartapplication.h"

DartApplication *DartApplication::createInstance()
{
    return new DartApplication();
}

DartApplication *DartApplication::createAndSetupInstance()
{
    auto app = DartApplication::createInstance()
            ->createModelsService()
            ->connectServices();
    return app;
}

DartApplication *DartApplication::createModelsService()
{
    registerTypes();
    _modelsService = _modelsServiceBuilder->createLocalModelsServiceWithJsonDb();
    return this;
}

DartApplication *DartApplication::connectServices()
{
    _connectRouteByGameMode->service(_modelsService,_routeTournamentByGameMode);
    _connectModelsServiceInterface->connectModelsInterface(this,_modelsService);
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

DartApplication *DartApplication::useThreads()
{
    try {
        _modelsService->moveToThread(_modelsContextInterfaceThread);
        startModelsContextInterfaceThread();
    }  catch (...) {
        // Implement some error functionality here
        return this;
    }
    setUsingThreads(true);
    return this;
}

void DartApplication::registerTypes()
{
    qRegisterMetaType<QByteArray>("QByteArray");
    qRegisterMetaType<AbstractApplicationInterface*>("AbstractApplicationInterface");
    qRegisterMetaType<AbstractModelsService*>("AbstractModelsService");
    qRegisterMetaType<AbstractGameController*>("AbstractGameController");
    qRegisterMetaType<AbstractDartsController*>("AbstractDartsController");
}

void DartApplication::handleTournamentsRequest(){
    emit requestTournaments();
}

void DartApplication::handleSetCurrentTournamentRequest(const int &index)
{
    emit setCurrentActiveTournament(index);
}

void DartApplication::handleDartsDetails(const QByteArray& json)
{
    emit sendDartsDetails(json);
}

void DartApplication::handleSendGameModesRequest() const
{
    QStringList resultingList;

    QString first = printVariable(FirstToPost);
    QString second = printVariable(RoundLimit);
    QString third = printVariable(Circular);

    resultingList << first << second << third;

    emit sendGameModes(resultingList);
}

void DartApplication::assembleDartsTournamentValues()
{
    emit requestCurrentTournamentId();
}

void DartApplication::setDartsPointController(AbstractDartsController *controller)
{
    delete _gameController;
    _gameController = controller;
    _connectDartsPointController->connectController(controller,this,_modelsService,_routeDartsControllerByDisplayHint);
    emit requestWakeUp();
}

void DartApplication::setDartsScoreController(AbstractDartsController *controller)
{
    delete _gameController;
    _gameController = controller;
    _connectDartsScoreController->connectController(controller,this,_modelsService,_routeDartsControllerByDisplayHint);
    emit requestWakeUp();
}

DartApplication::DartApplication()
{
    auto dartsPointBuilderService = DartsBuilderContext::DartsPointControllerBuilder::createInstance()
            ->setBuildEntityByJson(DartsBuilderContext::BuildDartsControllerEntity::createInstance());
    auto dartsScoreBuilderService = DartsBuilderContext::DartsScoreBuilderService::createInstance()
            ->setBuildEntityByJson(DartsBuilderContext::BuildDartsControllerEntity::createInstance());
    _dartsPointBuilder = dartsPointBuilderService;
    _dartsScoreBuilder = dartsScoreBuilderService;
}

void DartApplication::clearGameController()
{
    _gameController->disconnect();
    delete _gameController;
    _gameController = nullptr;
}

void DartApplication::startModelsContextInterfaceThread()
{
    _modelsContextInterfaceThread->start();
}


void DartApplication::stopModelsInterfaceThread()
{
    _modelsContextInterfaceThread->terminate();
    _modelsContextInterfaceThread->wait();
}

AbstractGameController *DartApplication::gameController() const
{
    return _gameController;
}

bool DartApplication::usingThreads() const
{
    return _usingThreads;
}

void DartApplication::setUsingThreads(bool usingThreads)
{
    _usingThreads = usingThreads;
}

AbstractDartsControllerBuilder *DartApplication::controllerBuilder()
{
    return _dartsPointBuilder;
}

DartApplication* DartApplication::setModelsServiceBuilder(AbstractModelsServiceBuilder<AbstractModelsService> *modelsServiceBuilder)
{
    _modelsServiceBuilder = modelsServiceBuilder;
    return this;
}

DartApplication *DartApplication::setDartsPointBuilderService(ControllerBuilderInterface *builder)
{
    _dartsPointBuilder = dynamic_cast<AbstractDartsControllerBuilder*>(builder);
    return this;
}
