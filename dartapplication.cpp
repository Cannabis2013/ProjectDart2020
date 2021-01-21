#include "dartapplication.h"


DartApplication::~DartApplication()
{
    delete _modelsInterface;
    delete _gameController;
}

DartApplication *DartApplication::createInstance()
{
    return new DartApplication();
}

DartApplication *DartApplication::setup()
{
    registerTypes();
    connectModelInterfaces();

    return this;
}

DartApplication *DartApplication::useThreads()
{
    try {
        _modelsInterface->moveToThread(_modelsContextInterfaceThread);
        startModelsContextInterfaceThread();
    }  catch (...) {
        // Implement some error functionality here
        return this;
    }
    setUsingThreads(true);
    return this;
}

AbstractModelsContextInterface *DartApplication::modelsContextInterface()
{
    return _modelsInterface;
}

DartApplication *DartApplication::setModelsContextInterface(AbstractModelsContextInterface *context)
{
    _modelsInterface = context;
    return this;
}

void DartApplication::handleTournamentsRequest(){
    emit requestTournaments();
}

void DartApplication::handleSetCurrentTournamentRequest(const int &index)
{
    emit setCurrentActiveTournament(index);
}

void DartApplication::handleScoreBoardRequest()
{
    emit requestPlayerScores();
}

void DartApplication::handleFTPDetails(const QString &title,
                                       const QVector<int> &data,
                                       const QVector<int> &playerIndexes)
{
    emit sendFTPDetails(title,
                        data,
                        playerIndexes);
}

void DartApplication::handleCreatePlayer(const QString &playerName,
                                              const QString &email)
{
    emit requestCreatePlayer(playerName,email);
}

void DartApplication::handleDeletePlayer(const int &index)
{
    emit requestDeletePlayer(index);
}

void DartApplication::handleDeletePlayersRequest(const QVariantList &args)
{
    QVector<int> indexes;
    for (auto variant : args) {
        auto index = variant.toInt();
        indexes << index;
    }
    emit requestDeletePlayers(indexes);
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

void DartApplication::handleUserInput(const int &point, const int &pressedModfier)
{
    emit sendPoint(point,pressedModfier);
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

void DartApplication::handleDeleteTournamentsRequest(const QVariantList &indexes)
{
    QVector<int> tournamentIndexes;
    for (auto variant : indexes)
        tournamentIndexes << variant.toInt();

    emit requestDeleteTournaments(tournamentIndexes);
}

void DartApplication::handleTournamentMetaRequest()
{
    emit requestTournamentMetaData();
}

void DartApplication::setGameController(AbstractGameController *controller)
{
    if(_gameController != nullptr)
        _gameController->disconnect();
    _gameController = controller;
    connectControllerInterface();
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
     * Setup upstream communication between UI and modelcontexts
     */
    connect(_modelsInterface,&AbstractModelsContextInterface::transmitResponse,
            this,&DartApplication::transmitResponse);
    /*
     * Get all tournaments
     */
    connect(this,&DartApplication::requestTournaments,
            _modelsInterface,&AbstractModelsContextInterface::handleTransmitTournamentData);
    connect(_modelsInterface,&AbstractModelsContextInterface::sendTournament,
            this,&DartApplication::sendRequestedTournament);
    connect(_modelsInterface,&AbstractModelsContextInterface::lastTournamentTransmitted,
            this,&DartApplication::lastTournamentDetailsTransmitted);
    /*
     * Get all players
     */
    connect(this,&DartApplication::requestPlayers,
            _modelsInterface,&AbstractModelsContextInterface::handleRequestPlayersDetails);
    connect(_modelsInterface,&AbstractModelsContextInterface::sendPlayerDetails,
            this,&DartApplication::sendPlayerDetail);
    connect(_modelsInterface,&AbstractModelsContextInterface::lastPlayerDetailTransmitted,
            this,&DartApplication::lastPlayerDetailsTransmitted);
    /*
     * Create tournament
     */
    connect(this,&DartApplication::sendFTPDetails,
            _modelsInterface,&AbstractModelsContextInterface::handleRequestForAddFTPTournament);
    /*
     * Create player
     */
    connect(this,&DartApplication::requestCreatePlayer,
            _modelsInterface,&AbstractModelsContextInterface::handleCreatePlayer);
    connect(_modelsInterface,&AbstractModelsContextInterface::confirmPlayerCreated,
            this,&DartApplication::playerCreatedSuccess);
    /*
     * Delete tournament
     */
    connect(this,&DartApplication::requestDeleteTournaments,
            _modelsInterface,&AbstractModelsContextInterface::handleDeleteTournaments);
    connect(_modelsInterface,&AbstractModelsContextInterface::tournamentsDeletedSuccess,
            this,&DartApplication::tournamentsDeletedSuccess);
    /*
     * Delete player{s}
     */
    connect(this,&DartApplication::requestDeletePlayer,
            _modelsInterface,&AbstractModelsContextInterface::handleDeletePlayerFromIndex);
    connect(this,&DartApplication::requestDeletePlayers,
            _modelsInterface,&AbstractModelsContextInterface::handleDeletePlayersFromIndexes);
    connect(_modelsInterface,&AbstractModelsContextInterface::playersDeletedStatus,
            this,&DartApplication::playersDeletedStatus);
    /*
     * Send tournament meta information
     */
    connect(_modelsInterface,&AbstractModelsContextInterface::sendTournamentMeta,
            this,&DartApplication::sendTournamentMetaData);
    /*
     * Send scorepoints
     */
    connect(_modelsInterface,&AbstractModelsContextInterface::sendPlayerScore,
            this,&DartApplication::sendPlayerScore);
}

void DartApplication::connectControllerInterface()
{
    /*
     * Establish communication between controller and UI
     */
    connect(_gameController,&AbstractGameController::transmitResponse,
            this,&DartApplication::transmitResponse);
    /*
     * Send tournament metadata
     */
    connect(this,&DartApplication::requestTournamentMetaData,
            _gameController,&AbstractGameController::handleRequestForCurrentTournamentMetaData);
    connect(_gameController,&AbstractGameController::requestTournamentMetaData,
            _modelsInterface,&AbstractModelsContextInterface::handleRequestForTournamentMetaData);
    /*
     * Setup request transmitting playerscores
     */
    connect(this,&DartApplication::requestPlayerScores,
            _gameController,&AbstractGameController::handleRequestForPlayerScores);
    connect(_gameController,&AbstractGameController::requestTransmitPlayerScores,
            _modelsInterface,&AbstractModelsContextInterface::handleTransmitPlayerScores);
    /*
     * Wake up controller
     */
    connect(this,&DartApplication::requestWakeUp,
            _gameController,&AbstractGameController::handleWakeUpRequest);
    /*
     * Start/stop game
     */
    connect(this,&DartApplication::requestStartGame,
            _gameController,&AbstractGameController::start);
    connect(this,&DartApplication::requestStopGame,
            _gameController,&AbstractGameController::stop);
    /*
     * Reset tournament
     */
    connect(this,&DartApplication::requestTournamentReset,
            _gameController,&AbstractGameController::handleResetTournament);
    connect(_gameController,&AbstractGameController::requestResetTournament,
            _modelsInterface,&AbstractModelsContextInterface::handleResetTournament);
    connect(_modelsInterface,&AbstractModelsContextInterface::tournamentResetSuccess,
            _gameController,&AbstractGameController::handleTournamentResetSuccess);
    /*
     * Add point
     */
    connect(this,&DartApplication::requestControllerState,
            _gameController,&AbstractGameController::handleRequestFromUI);
    connect(this,&DartApplication::sendPoint,
            _gameController,&AbstractGameController::handleAndProcessUserInput);
    connect(_gameController,&AbstractGameController::requestAddScore,
            _modelsInterface,&AbstractModelsContextInterface::handleAddScore);
    connect(_modelsInterface,&AbstractModelsContextInterface::scoreAddedToDataContext,
            _gameController,&AbstractGameController::handleScoreAddedToDataContext);
    /*
     * Undo/redo
     */
    connect(this,&DartApplication::requestUndo,
            _gameController,&AbstractGameController::undoTurn);
    connect(this,&DartApplication::requestRedo,
            _gameController,&AbstractGameController::redoTurn);
    connect(_gameController,&AbstractGameController::requestSetModelHint,
            _modelsInterface,&AbstractModelsContextInterface::handleRequestSetScoreHint);
    connect(_modelsInterface,&AbstractModelsContextInterface::scoreHintUpdated,
            _gameController,&AbstractGameController::handleScoreHintUpdated);
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

AbstractModelsContextInterface *DartApplication::modelsInterface() const
{
    return _modelsInterface;
}

DartApplication *DartApplication::setModelsInterface(AbstractModelsContextInterface *modelsInterface)
{
    _modelsInterface = modelsInterface;
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

DartApplication *DartApplication::setControllerBuilder(AbstractControllerBuilder* builder)
{
    _controllerBuilder = builder;
    /*
     * Connect interface
     */
    connect(this,&DartApplication::setCurrentActiveTournament,
            _modelsInterface,&AbstractModelsContextInterface::handleRequestTournamentGameMode);
    connect(_modelsInterface,&AbstractModelsContextInterface::sendTournamentGameMode,
            _controllerBuilder,&AbstractControllerBuilder::handleRecieveGameMode);
    connect(_controllerBuilder,&AbstractControllerBuilder::requestFTPDetails,
            _modelsInterface,&AbstractModelsContextInterface::handleRequestFTPDetails);
    connect(_modelsInterface,&AbstractModelsContextInterface::sendTournamentFTPDetails,
            _controllerBuilder,&AbstractControllerBuilder::assembleFTPGameController);
    connect(_controllerBuilder,&AbstractControllerBuilder::sendController,
            this,&DartApplication::setGameController);
    return this;
}
