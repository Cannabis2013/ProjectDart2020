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
    registerTypes();
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
    emit requestTournaments();
}

void DartApplication::handleSetCurrentTournamentRequest(const int &index)
{
    emit setCurrentActiveTournament(index);
}

void DartApplication::handleRequestForSingleThrowScoreData()
{
    emit requestSingleThrowPlayerScores();
}

void DartApplication::handleRequestForMultiThrowScoreData()
{
    emit requestFtpMultiAttemptScores();
}

void DartApplication::handleFTPDetails(const QByteArray& json)
{
    emit sendFTPDetails(json);
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

void DartApplication::handleUserInput(const QByteArray& json)
{
    emit sendPoint(json);
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

void DartApplication::handleTournamentMetaRequest()
{
    emit requestCurrentTournamentId();
}

void DartApplication::assembleAndConfigureControllerBuilder(const QByteArray& json)
{
    emit assembleFTPController(json,this,_modelsContext);
}

void DartApplication::setGameController(AbstractGameController *controller)
{
    delete _gameController;
    _gameController = controller;
    emit requestWakeUp();
}

void DartApplication::registerTypes()
{
    /*
     * Register meta types
     */
    qRegisterMetaType<QVector<QString>>("QVector<QString>");
    qRegisterMetaType<QVector<QUuid>>("QVector<QUuid>");
    qRegisterMetaType<QVector<int>>("QVector<int>");
}

void DartApplication::connectModelInterfaces()
{
    /*
     * Get all tournaments
     */
    connect(this,&DartApplication::requestTournaments,
            _modelsContext,&AbstractModelsContext::handleRequestTournaments);
    connect(_modelsContext,&AbstractModelsContext::sendTournament,
            this,&DartApplication::sendRequestedTournament);
    connect(_modelsContext,&AbstractModelsContext::sendTournaments,
            this,&DartApplication::sendTournaments);
    /*
     * Get all players
     */
    connect(this,&DartApplication::requestPlayers,
            _modelsContext,&AbstractModelsContext::handleRequestPlayersDetails);
    connect(_modelsContext,&AbstractModelsContext::sendPlayers,
            this,&DartApplication::sendPlayers);
    /*
     * Create tournament
     */
    connect(this,&DartApplication::sendFTPDetails,
            _modelsContext,&AbstractModelsContext::addFTPTournament);
    connect(_modelsContext,&AbstractModelsContext::tournamentAssembledAndStored,
            this,&AbstractApplicationInterface::tournamentAssembledAndStored);
    /*
     * Create player
     */
    connect(this,&DartApplication::requestCreatePlayer,
            _modelsContext,&AbstractModelsContext::createPlayer);
    connect(_modelsContext,&AbstractModelsContext::createPlayerResponse,
            this,&DartApplication::createPlayerResponse);
    /*
     * Delete tournament
     */
    connect(this,&DartApplication::requestDeleteTournaments,
            _modelsContext,&AbstractModelsContext::deleteTournaments);
    connect(_modelsContext,&AbstractModelsContext::tournamentsDeletedStatus,
            this,&DartApplication::tournamentsDeletedSuccess);
    /*
     * Delete player{s}
     */
    connect(this,&DartApplication::requestDeletePlayer,
            _modelsContext,&AbstractModelsContext::deletePlayerFromIndex);
    connect(this,&DartApplication::requestDeletePlayers,
            _modelsContext,&AbstractModelsContext::deletePlayersFromIndexes);
    connect(_modelsContext,&AbstractModelsContext::playersDeletedStatus,
            this,&DartApplication::playersDeletedStatus);
    /*
     * Send tournament meta information
     */
    connect(_modelsContext,&AbstractModelsContext::sendTournamentMeta,
            this,&DartApplication::sendFTPTournamentMetaData);
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

AbstractModelsContext *DartApplication::modelsContextInterface() const
{
    return _modelsContext;
}

DartApplication *DartApplication::setModelsContextInterface(AbstractModelsContext *modelsInterface)
{
    _modelsContext = modelsInterface;
    connectModelInterfaces();
    return this;
}

bool DartApplication::usingThreads() const
{
    return _usingThreads;
}

void DartApplication::setUsingThreads(bool usingThreads)
{
    _usingThreads = usingThreads;
}

AbstractControllerBuilder *DartApplication::controllerBuilder()
{
    return _controllerBuilder;
}

DartApplication *DartApplication::setControllerBuilder(ControllerBuilderInterface *builder)
{
    _controllerBuilder = dynamic_cast<AbstractControllerBuilder*>(builder);
    /*
     * Connect interface
     */
    connect(this,&DartApplication::setCurrentActiveTournament,
            _modelsContext,&AbstractModelsContext::handleRequestGameMode);
    connect(_modelsContext,&AbstractModelsContext::requestAssembleTournament,
            _controllerBuilder,&AbstractControllerBuilder::determineTournamentGameMode);
    connect(_controllerBuilder,&AbstractControllerBuilder::requestFTPDetails,
            _modelsContext,&AbstractModelsContext::assembleFtpKeyValues);
    connect(_modelsContext,&AbstractModelsContext::sendTournamentFtpDetails,
            this,&DartApplication::assembleAndConfigureControllerBuilder);
    connect(this,&DartApplication::assembleFTPController,
            _controllerBuilder,&AbstractControllerBuilder::assembleFTPGameController);
    connect(_controllerBuilder,&AbstractControllerBuilder::sendController,
            this,&DartApplication::setGameController);
    return this;
}
