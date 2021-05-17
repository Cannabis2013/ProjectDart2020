#include "dartapplication.h"


DartApplication::~DartApplication()
{
    delete _modelsContext;
    delete _gameController;
}

DartApplication *DartApplication::createInstance()
{
    return new DartApplication();
}

DartApplication *DartApplication::setup()
{
    _modelsContext = _modelsServiceBuilder->buildLocalModelsServiceWithJsonDb();
    _connectModelsServiceInterface->service(this,_modelsContext);
    _connectControllerBuilder->service(this,_controllerBuilder,_modelsContext);
    return this;
}

DartApplication *DartApplication::useThreads()
{
    try {
        _modelsContext->moveToThread(_modelsContextInterfaceThread);
        startModelsContextInterfaceThread();
    }  catch (...) {
        // Implement some error functionality here
        return this;
    }
    setUsingThreads(true);
    return this;
}

void DartApplication::handleTournamentsRequest(){
    cout << "requestTournaments" << endl;
    emit requestTournaments();
}

void DartApplication::handleSetCurrentTournamentRequest(const int &index)
{
    cout << "handleSetCurrentTournamentRequest" << endl;
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

void DartApplication::assembleAndConfigureControllerBuilder(const QByteArray& json)
{
    emit assembleDartsController(json,this,_modelsContext);
}

void DartApplication::setGameController(AbstractGameController *controller)
{
    delete _gameController;
    _gameController = controller;
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
    return _controllerBuilder;
}

DartApplication *DartApplication::setConnectControllerBuilder(ITernaryService<AbstractApplicationInterface *, AbstractDartsControllerBuilder *, AbstractModelsService *, void> *connectControllerBuilder)
{
    _connectControllerBuilder = connectControllerBuilder;
    return this;
}

DartApplication* DartApplication::setConnectModelsServiceInterface(IBinaryService<AbstractApplicationInterface *, AbstractModelsService *, void> *connectModelsServiceInterface)
{
    _connectModelsServiceInterface = connectModelsServiceInterface;
    return this;
}

DartApplication* DartApplication::setModelsServiceBuilder(AbstractModelsServiceBuilder<AbstractModelsService> *modelsServiceBuilder)
{
    _modelsServiceBuilder = modelsServiceBuilder;
    return this;
}

DartApplication *DartApplication::setControllerBuilder(ControllerBuilderInterface *builder)
{
    _controllerBuilder = dynamic_cast<AbstractDartsControllerBuilder*>(builder);
    return this;
}
