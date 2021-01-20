#include "dartapplication.h"


DartApplication::~DartApplication()
{
    delete _tournamentModelsContext;
    delete _playerModelsContext;
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
        _tournamentModelsContext->moveToThread(_tournamentModelsThread);
        _playerModelsContext->moveToThread(_playerModelsThread);
        startTournamentModelsWorkerThread();
        startPlayerModelsWorkerThread();
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

void DartApplication::handleScoreBoardRequest()
{
    emit requestPlayerScores();
}

void DartApplication::handleCreateTournament(const QString &title,
                                                  const QList<int> &data,
                                                  const QVariantList &playerIndexes)
{
    QList<int> indexes;
    for (auto variant : playerIndexes)
        indexes << variant.toInt();

    emit sendTournamentCandidate(title,
                                 data,
                                 indexes);
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

void DartApplication::processRecievedTournamentMetaData(const QString &title,
                                                             const int &gameMode,
                                                             const int &keyPoint,
                                                             const int &tableViewHint,
                                                             const int &inputMode,
                                                             const QString &winnerName,
                                                             const QStringList &assignedPlayerNames)
{
    QVariantList args = {title,
                         gameMode,
                         keyPoint,
                         tableViewHint,
                         inputMode,
                         assignedPlayerNames,
                         winnerName};
    emit sendTournamentMetaData(args);
}

void DartApplication::handleTournamentDetailsAndSetController(const QUuid& tournament,
                                                              const QUuid& winner,
                                                              const QList<int>& parameters,
                                                              const QList<QUuid>& playerIds,
                                                              const QList<QString>& playerNames)
{
    if(_gameController != nullptr)
        clearGameController();
    auto gameMode = parameters.at(0);
    if(gameMode == GameModes::FirstToPost)
    {
        /*
         * Build and inject game controller
         */

        _gameController = controllerBuilder()->assembleFTPGameController(tournament,
                                                                         winner,
                                                                         parameters,
                                                                         playerIds,
                                                                         playerNames);
        // Connect interfaces
        connectControllerInterface();
        // If using threads, move controller to its designated thread
        if(usingThreads())
        {
            _gameController->moveToThread(_gameControllerThread);
            _gameControllerThread->start();
        };
        emit requestWakeUp();
    }
}

void DartApplication::registerTypes()
{
    /*
     * Register meta types
     */
    qRegisterMetaType<QList<QUuid>>("QList<QUuid>");
    qRegisterMetaType<QList<int>>("QList<int>");
}

void DartApplication::connectModelInterfaces()
{
    /*
     * Setup upstream communication between UI and modelcontexts
     */
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::transmitResponse,
            this,&DartApplication::transmitResponse);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::transmitResponse,
            this,&DartApplication::transmitResponse);
    /*
     * Get all tournaments
     */
    connect(this,&DartApplication::requestTournaments,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleTransmitTournaments);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::sendTournament,
            this,&DartApplication::sendRequestedTournament);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::lastTournamentTransmitted,
            this,&DartApplication::lastTournamentDetailsTransmitted);
    /*
     * Get all players
     */
    connect(this,&DartApplication::requestPlayers,
            _playerModelsContext,&AbstractPlayerModelsContext::handleRequestPlayersDetails);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::sendPlayerDetails,
            this,&DartApplication::sendPlayerDetail);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::lastPlayerDetailTransmitted,
            this,&DartApplication::lastPlayerDetailsTransmitted);
    /*
     * Create tournament
     */
    connect(this,&DartApplication::sendTournamentCandidate,
            _playerModelsContext,&AbstractPlayerModelsContext::handleAndProcessCreatedTournament);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::sendProcessedTournamentDetails,
            _tournamentModelsContext,&AbstractTournamentModelsContext::assembleAndAddTournament);
    /*
     * Create player
     */
    connect(this,&DartApplication::requestCreatePlayer,
            _playerModelsContext,&AbstractPlayerModelsContext::createPlayer);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::confirmPlayerCreated,
            this,&DartApplication::playerCreatedSuccess);
    /*
     * Delete tournament
     */
    connect(this,&DartApplication::requestDeleteTournaments,
            _tournamentModelsContext,&AbstractTournamentModelsContext::deleteTournaments);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::tournamentsDeletedSuccess,
            this,&DartApplication::tournamentsDeletedSuccess);
    /*
     * Delete player{s}
     */
    connect(this,&DartApplication::requestDeletePlayer,
            _playerModelsContext,&AbstractPlayerModelsContext::deletePlayer);
    connect(this,&DartApplication::requestDeletePlayers,
            _playerModelsContext,&AbstractPlayerModelsContext::deletePlayers);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::playersDeletedStatus,
            this,&DartApplication::playersDeletedStatus);
    /*
     * Set current tournament
     */
    connect(this,&DartApplication::setCurrentActiveTournament,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestTournamentGameMode);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::sendTournamentDetails,
            _playerModelsContext,&AbstractPlayerModelsContext::processTournamentDetails);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::sendTournamentDetails,
            this,&DartApplication::handleTournamentDetailsAndSetController);
    /*
     * Send tournament meta information
     */
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::sendTournamentMeta,
            _playerModelsContext,&AbstractPlayerModelsContext::handleAndProcessTournamentMetaData);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::sendProcessedTournamentMetaData,
            this,&DartApplication::processRecievedTournamentMetaData);
    /*
     * Send scorepoints
     */
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::sendPlayerScore,
            this,&DartApplication::sendPlayerScore);
}

void DartApplication::connectControllerInterface()
{
    /*
    stopTournamentModelsWorkerThread();
    stopPlayerModelsWorkerThread();
    */
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
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestForTournamentMetaData);
    /*
     * Setup request transmitting playerscores
     */
    connect(this,&DartApplication::requestPlayerScores,
            _gameController,&AbstractGameController::handleRequestForPlayerScores);
    connect(_gameController,&AbstractGameController::sendAssignedTournamentPlayers,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleTransmitPlayerScores);
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
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleResetTournament);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::tournamentResetSuccess,
            _gameController,&AbstractGameController::handleTournamentResetSuccess);
    /*
     * Add point
     */
    connect(this,&DartApplication::requestControllerState,
            _gameController,&AbstractGameController::handleRequestFromUI);
    connect(this,&DartApplication::sendPoint,
            _gameController,&AbstractGameController::handleAndProcessUserInput);
    connect(_gameController,&AbstractGameController::requestAddScore,
            _tournamentModelsContext,&AbstractTournamentModelsContext::addScore);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::scoreAddedToDataContext,
            _gameController,&AbstractGameController::handleScoreAddedToDataContext);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::datacontextUpdated,
            _gameController,&AbstractGameController::handleDataContextUpdated);
    /*
     * Undo/redo
     */
    connect(this,&DartApplication::requestUndo,
            _gameController,&AbstractGameController::undoTurn);
    connect(this,&DartApplication::requestRedo,
            _gameController,&AbstractGameController::redoTurn);
    connect(_gameController,&AbstractGameController::requestSetModelHint,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestSetScoreHint);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::scoreHintUpdated,
            _gameController,&AbstractGameController::handleScoreHintUpdated);
}

void DartApplication::clearGameController()
{
    _gameController->disconnect();
    delete _gameController;
    _gameController = nullptr;
}

void DartApplication::startTournamentModelsWorkerThread()
{
    _tournamentModelsThread->start();
}

void DartApplication::startPlayerModelsWorkerThread()
{
    _playerModelsThread->start();
}

void DartApplication::stopTournamentModelsWorkerThread()
{
    _tournamentModelsThread->terminate();
    _tournamentModelsThread->wait();
}

void DartApplication::stopPlayerModelsWorkerThread()
{
    _playerModelsThread->terminate();
    _playerModelsThread->wait();
}

AbstractGameController *DartApplication::gameController() const
{
    return _gameController;
}

IDefaultGameBuilder *DartApplication::controllerBuilder() const
{
    return _controllerBuilder;
}

bool DartApplication::usingThreads() const
{
    return _usingThreads;
}

void DartApplication::setUsingThreads(bool usingThreads)
{
    _usingThreads = usingThreads;
}

AbstractPlayerModelsContext *DartApplication::playerModelsContext() const
{
    return _playerModelsContext;
}

DartApplication *DartApplication::setPlayerModelsContext(AbstractPlayerModelsContext *playerModelsContext)
{
    _playerModelsContext = playerModelsContext;
    return this;
}

IDefaultGameBuilder *DartApplication::controllerBuilder()
{
    return _controllerBuilder;
}

DartApplication *DartApplication::setControllerBuilder(IDefaultGameBuilder *builder)
{
    _controllerBuilder = builder;
    return this;
}

AbstractTournamentModelsContext *DartApplication::tournamentsModelContext() const
{
    return _tournamentModelsContext;
}

DartApplication *DartApplication::setTournamentsModelContext(AbstractTournamentModelsContext *tournamentsModelContext)
{
    _tournamentModelsContext = tournamentsModelContext;
    return this;
}
