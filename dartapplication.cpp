#include "dartapplication.h"

DartApplication *DartApplication::createInstance()
{
    return new DartApplication();
}

DartApplication *DartApplication::setup()
{
    registerTypes();
    _modelsService = _modelsServiceBuilder->buildLocalModelsServiceWithJsonDb();
    _connectRouteByGameMode->service(_modelsService,_routeTournamentByGameMode);
    _connectModelsServiceInterface->connectModelsInterface(this,_modelsService);
    _connectRouteByInputHint->connectServices(_modelsService,_routeDartsControllerByInputHint);
    /*
     * Connect darts builder services
     */
    _connectDartsPointBuilder->connectServices(_routeDartsControllerByInputHint,_dartsPointBuilder,this);
    _connectDartsScoreBuilder->connectServices(_routeDartsControllerByInputHint,_dartsScoreBuilder,this);
    /*
     * Connect route from the point where controllers are initialized the route interface
     */
    _connectDartsPointRoute->connectServices(_routeDartsControllerByDisplayHint,this);
    _connectDartsScoreRoute->connectServices(_routeDartsControllerByDisplayHint,this);
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

void DartApplication::handleRequestForDartsSingleAttemptPoints()
{
    emit requestDartsSingleAttemptPoints();
}

void DartApplication::handleRequestForMultiAttemptScores()
{
    emit requestDartsMultiAttemptScores();
}

void DartApplication::handleFTPDetails(const QByteArray& json)
{
    cout << "sendtournaments" << endl;
    emit sendDartsDetails(json);
}

void DartApplication::handleCreatePlayer(const QByteArray &json)
{
    emit requestCreatePlayer(json);
}

void DartApplication::handleDeletePlayer(const QByteArray& json)
{
    emit requestDeletePlayer(json);
}

void DartApplication::handleDeletePlayersRequest(const QByteArray& json)
{
    emit requestDeletePlayers(json);
}

void DartApplication::requestPlayerDetails()
{
    emit requestPlayers();
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

void DartApplication::handleRestartTournament()
{
    emit requestTournamentReset();
}

void DartApplication::handleRequestStart()
{
    emit requestStartGame();
}

void DartApplication::handleRequestStop()
{
    emit requestStopGame();
}

void DartApplication::handleDartsSingleAttemptInput(const QByteArray& json)
{
    emit sendDartsSingleAttemptPoint(json);
}

void DartApplication::handleDartsMultiAttemptInput(const QByteArray &json)
{
    emit sendDartsMultiAttemptScore(json);
}

void DartApplication::handleUndoRequest()
{
    emit requestUndo();
}

void DartApplication::handleRedoRequest()
{
    emit requestRedo();
}

void DartApplication::handleControllerStateRequest()
{
    emit requestControllerState();
}

void DartApplication::handleDeleteTournamentsRequest(const QByteArray& json)
{
    emit requestDeleteTournaments(json);
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

DartApplication *DartApplication::setConnectDartsScoreRoute(IConnectRouteByDisplayHint *newConnectDartsScoreRoute)
{
    _connectDartsScoreRoute = newConnectDartsScoreRoute;
    return this;
}

DartApplication *DartApplication::setConnectDartsPointRoute(IConnectRouteByDisplayHint *newConnectDartsPointRoute)
{
    _connectDartsPointRoute = newConnectDartsPointRoute;
    return this;
}

DartApplication *DartApplication::setRouteDartsControllerByDisplayHint(AbstractRouteDartsByDisplayHint *service)
{
    _routeDartsControllerByDisplayHint = service;
    return this;
}

DartApplication *DartApplication::setRouteByInputHint(AbstractRouteByInputHint *newRouteByInputHint)
{
    _routeDartsControllerByInputHint = newRouteByInputHint;
    return this;
}

DartApplication *DartApplication::setConnectRouteByInputHint(IConnectRouteByInputHint *newConnectRouteByInputHint)
{
    _connectRouteByInputHint = newConnectRouteByInputHint;
    return this;
}

DartApplication *DartApplication::setRouteByDisplayHint(AbstractRouteDartsByDisplayHint *newRouteByDisplayHint)
{
    _routeDartsControllerByDisplayHint = newRouteByDisplayHint;
    return this;
}

DartApplication *DartApplication::setConnectDartsScoreController(IConnectDartsScoreController *newConnectDartsScoreController)
{
    _connectDartsScoreController = newConnectDartsScoreController;
    return this;
}

DartApplication *DartApplication::setConnectDartsPointController(IConnectDartsPointController *newConnectDartsPointController)
{
    _connectDartsPointController = newConnectDartsPointController;
    return this;
}

DartApplication *DartApplication::setConnectToDartsScoreBuilder(IConnectRouteToDartsBuilder *newConnectToDartsScoreBuilder)
{
    _connectDartsScoreBuilder = newConnectToDartsScoreBuilder;
    return this;
}

DartApplication *DartApplication::setConnectToDartsPountBuilder(IConnectRouteToDartsBuilder *newConnectToDartsPountBuilder)
{
    _connectDartsPointBuilder = newConnectToDartsPountBuilder;
    return this;
}

DartApplication *DartApplication::setDartsScoreBuilder(AbstractDartsControllerBuilder *service)
{
    _dartsScoreBuilder = service;
    return this;
}

DartApplication *DartApplication::setDartsScoreControllerBuilder(AbstractDartsControllerBuilder *service)
{
    _dartsScoreBuilder = service;
    return this;
}

DartApplication *DartApplication::setConnectRouteByGameMode(ConnectRouteByGameMode *newConnectTournamentGameModeService)
{
    _connectRouteByGameMode = newConnectTournamentGameModeService;
    return this;
}

DartApplication *DartApplication::setDetermineTournamentGameMode(AbstractRouteByGameMode *newDetermineTournamentGameMode)
{
    _routeTournamentByGameMode = newDetermineTournamentGameMode;
    return this;
}

DartApplication* DartApplication::setConnectModelsServiceInterface(IConnectModelsInterface *connectModelsServiceInterface)
{
    _connectModelsServiceInterface = connectModelsServiceInterface;
    return this;
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
