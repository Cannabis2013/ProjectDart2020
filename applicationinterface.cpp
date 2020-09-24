#include "applicationinterface.h"


ApplicationInterface::~ApplicationInterface()
{
    delete _tournamentModelsContext;
    delete _playerModelsContext;
    delete _gameController;
}

ApplicationInterface *ApplicationInterface::setup()
{
    registerTypes();
    connectModelInterfaces();

    return this;
}

ApplicationInterface *ApplicationInterface::useThreads()
{
    _tournamentModelsContext->moveToThread(_tournamentModelsThread);
    _playerModelsContext->moveToThread(_playerModelsThread);
    _tournamentModelsThread->start();
    _playerModelsThread->start();
    return this;
}

void ApplicationInterface::handleTournamentsRequest(){
    emit requestTournaments();
}

void ApplicationInterface::handleSetCurrentTournamentRequest(const int &index)
{
    emit setCurrentActiveTournament(index);
}

void ApplicationInterface::handleScoreBoardRequest()
{
    emit requestPlayerScores();
}

void ApplicationInterface::handleCreateTournament(const QString &title,
                                                  const int &numberOfThrows,
                                                  const int &gameMode,
                                                  const int &winCondition,
                                                  const int &keyPoint,
                                                  const QVariantList &playerIndexes)
{
    QList<int> indexes;
    for (auto variant : playerIndexes)
        indexes << variant.toInt();

    emit sendTournamentCandidate(title,numberOfThrows,gameMode,winCondition,keyPoint,indexes);
}

void ApplicationInterface::handleCreatePlayer(const QString &playerName, const QString &email)
{
    emit requestCreatePlayer(playerName,email);
}

void ApplicationInterface::handleDeletePlayer(const int &index)
{
    emit requestDeletePlayer(index);
}

void ApplicationInterface::handleDeletePlayersRequest(const QVariantList &args)
{
    QVector<int> indexes;
    for (auto variant : args) {
        auto index = variant.toInt();
        indexes << index;
    }
    emit requestDeletePlayers(indexes);
}

void ApplicationInterface::requestPlayerDetails()
{
    emit requestPlayers();
}

void ApplicationInterface::handleSendGameModesRequest() const
{
    QStringList resultingList;

    QString first = printVariable(FirstToPost);
    QString second = printVariable(RoundLimit);
    QString third = printVariable(Circular);

    resultingList << first << second << third;

    emit sendGameModes(resultingList);
}

void ApplicationInterface::handleRestartTournament()
{
    emit requestTournamentReset();
}

void ApplicationInterface::handleRequestStart()
{
    emit requestStartGame();
}

void ApplicationInterface::handleRequestStop()
{
    emit requestStopGame();
}

void ApplicationInterface::handleUserInput(const int &point, const int &pressedModfier)
{
    emit sendPoint(point,pressedModfier);
}

void ApplicationInterface::handleUndoRequest()
{
    emit requestUndo();
}

void ApplicationInterface::handleRedoRequest()
{
    emit requestRedo();
}

void ApplicationInterface::handleControllerStateRequest()
{
    emit requestControllerState();
}

void ApplicationInterface::handleDeleteTournamentsRequest(const QVariantList &indexes)
{
    QVector<int> tournamentIndexes;
    for (auto variant : indexes)
        tournamentIndexes << variant.toInt();

    emit requestDeleteTournaments(tournamentIndexes);
}

void ApplicationInterface::handleTournamentMetaRequest()
{
    emit requestTournamentMetaData();
}

void ApplicationInterface::processRecievedTournamentMetaData(const QString &title,
                                                             const int &gameMode,
                                                             const int &keyPoint,
                                                             const QString &winnerName,
                                                             const QStringList &assignedPlayerNames)
{
    QVariantList args = {title,
                         gameMode,
                         keyPoint,
                         assignedPlayerNames,
                         winnerName};
    emit sendTournamentMetaData(args);
}

void ApplicationInterface::handleTournamentDetailsAndSetController(const QUuid &tournament,
                                                                   const QString &winner,
                                                                   const int &keyPoint,
                                                                   const int &terminalKeyCode,
                                                                   const int &numberOfThrows,
                                                                   const int &gameMode,
                                                                   const PlayerPairs &assignedPlayerPairs)
{
    if(_gameController != nullptr)
    {
        _gameController->disconnect();
        delete _gameController;
        _gameController = nullptr;
    }
    if(gameMode == GameModes::FirstToPost)
    {
        /*
         * Inject controller
         */
        _gameController = _controllerBuilder->buildController(gameMode,0x4);
        connectControllerInterface();
        emit sendTournamentDetails(tournament,
                                   winner,
                                   keyPoint,
                                   terminalKeyCode,
                                   numberOfThrows,
                                   assignedPlayerPairs);
    }
}

void ApplicationInterface::registerTypes()
{
    /*
     * Register meta types
     */
    qRegisterMetaType<PlayerPair>("PlayerPair");
    qRegisterMetaType<PlayerPairs>("PlayerPairs");
    qRegisterMetaType<QList<QUuid>>("QList<QUuid>");
}

void ApplicationInterface::connectModelInterfaces()
{
    /*
     * Setup upstream communication between UI and modelcontexts
     */
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::transmitResponse,
            this,&ApplicationInterface::transmitResponse);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::transmitResponse,
            this,&ApplicationInterface::transmitResponse);
    /*
     * Get all tournaments
     */
    connect(this,&ApplicationInterface::requestTournaments,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleTransmitTournaments);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::sendTournament,
            this,&ApplicationInterface::sendRequestedTournament);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::lastTournamentTransmitted,
            this,&ApplicationInterface::lastTournamentDetailsTransmitted);
    /*
     * Get all players
     */
    connect(this,&ApplicationInterface::requestPlayers,
            _playerModelsContext,&AbstractPlayerModelsContext::handleRequestPlayersDetails);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::sendPlayerDetails,
            this,&ApplicationInterface::sendPlayerDetail);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::lastPlayerDetailTransmitted,
            this,&ApplicationInterface::lastPlayerDetailsTransmitted);
    /*
     * Create tournament
     */
    connect(this,&ApplicationInterface::sendTournamentCandidate,
            _playerModelsContext,&AbstractPlayerModelsContext::handleProcessCreatedTournament);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::sendProcessedTournamentDetails,
            _tournamentModelsContext,&AbstractTournamentModelsContext::assembleAndAddTournament);
    /*
     * Create player
     */
    connect(this,&ApplicationInterface::requestCreatePlayer,
            _playerModelsContext,&AbstractPlayerModelsContext::createPlayer);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::confirmPlayerCreated,
            this,&ApplicationInterface::playerCreatedSuccess);
    /*
     * Delete tournament
     */
    connect(this,&ApplicationInterface::requestDeleteTournaments,
            _tournamentModelsContext,&AbstractTournamentModelsContext::deleteTournaments);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::tournamentsDeletedSuccess,
            this,&ApplicationInterface::tournamentsDeletedSuccess);
    /*
     * Delete player{s}
     */
    connect(this,&ApplicationInterface::requestDeletePlayer,
            _playerModelsContext,&AbstractPlayerModelsContext::deletePlayer);
    connect(this,&ApplicationInterface::requestDeletePlayers,
            _playerModelsContext,&AbstractPlayerModelsContext::deletePlayers);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::playersDeletedStatus,
            this,&ApplicationInterface::playersDeletedStatus);
    /*
     * Set current tournament
     */
    connect(this,&ApplicationInterface::setCurrentActiveTournament,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestTournamentDetails);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::sendTournamentDetails,
            _playerModelsContext,&AbstractPlayerModelsContext::processTournamentDetails);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::sendTournamentDetails,
            this,&ApplicationInterface::handleTournamentDetailsAndSetController);
    /*
     * Send tournament meta information
     */
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::sendTournamentMeta,
            _playerModelsContext,&AbstractPlayerModelsContext::handleAndProcessTournamentMetaData);
    connect(_playerModelsContext,&AbstractPlayerModelsContext::sendProcessedTournamentMetaData,
            this,&ApplicationInterface::processRecievedTournamentMetaData);
    /*
     * Send scorepoints
     */
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::sendPlayerScore,
            this,&ApplicationInterface::sendPlayerScore);
}

void ApplicationInterface::connectControllerInterface()
{
    /*
    stopTournamentModelsWorkerThread();
    stopPlayerModelsWorkerThread();
    */
    /*
     * Establish communication between controller and UI
     */
    connect(_gameController,&AbstractGameController::transmitResponse,
            this,&ApplicationInterface::transmitResponse);
    /*
     * Set current tournament
     */
    connect(this,&ApplicationInterface::sendTournamentDetails,
            _gameController,&AbstractGameController::recieveTournamentDetails);
    connect(_gameController,&AbstractGameController::requestTournamentIndexes,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestTournamentIndexes);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::sendTournamentIndexes,
            _gameController,&AbstractGameController::recieveTournamentIndexes);
    /*
     * Send tournament metadata
     */
    connect(this,&ApplicationInterface::requestTournamentMetaData,
            _gameController,&AbstractGameController::handleRequestForCurrentTournamentMetaData);
    connect(_gameController,&AbstractGameController::requestTournamentMetaData,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestForTournamentMetaData);
    /*
     * Setup request transmitting playerscores
     */
    connect(this,&ApplicationInterface::requestPlayerScores,
            _gameController,&AbstractGameController::handleRequestForPlayerScores);
    connect(_gameController,&AbstractGameController::sendCurrentTournamentForTransmittingScorePoints,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleTransmitPlayerScores);
    /*
     * Start/stop game
     */
    connect(this,&ApplicationInterface::requestStartGame,
            _gameController,&AbstractGameController::start);
    connect(this,&ApplicationInterface::requestStopGame,
            _gameController,&AbstractGameController::stop);
    /*
     * Reset tournament
     */
    connect(this,&ApplicationInterface::requestTournamentReset,
            _gameController,&AbstractGameController::handleResetTournament);
    connect(_gameController,&AbstractGameController::requestResetTournament,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleResetTournament);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::tournamentResetSuccess,
            _gameController,&AbstractGameController::handleTournamentResetSuccess);
    /*
     * Add point
     */
    connect(this,&ApplicationInterface::requestControllerState,
            _gameController,&AbstractGameController::handleRequestFromUI);
    connect(this,&ApplicationInterface::sendPoint,
            _gameController,&AbstractGameController::handleAndProcessUserInput);
    connect(_gameController,&AbstractGameController::sendScore,
            _tournamentModelsContext,&AbstractTournamentModelsContext::addScore);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::scoreAddedToDataContext,
            _gameController,&AbstractGameController::handleScoreAddedToDataContext);
    connect(_gameController,&AbstractGameController::requestUpdateContext,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestUpdateContext);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::datacontextUpdated,
            _gameController,&AbstractGameController::handleDataContextUpdated);
    /*
     * Undo/redo
     */
    connect(this,&ApplicationInterface::requestUndo,
            _gameController,&AbstractGameController::undoTurn);
    connect(this,&ApplicationInterface::requestRedo,
            _gameController,&AbstractGameController::redoTurn);
    connect(_gameController,&AbstractGameController::requestSetModelHint,
            _tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestSetScoreHint);
    connect(_tournamentModelsContext,&AbstractTournamentModelsContext::scoreHintUpdated,
            _gameController,&AbstractGameController::handleScoreHintUpdated);

    startTournamentModelsWorkerThread();
    startPlayerModelsWorkerThread();
}

void ApplicationInterface::startTournamentModelsWorkerThread()
{
    _tournamentModelsThread->start();
}

void ApplicationInterface::startPlayerModelsWorkerThread()
{
    _playerModelsThread->start();
}

void ApplicationInterface::stopTournamentModelsWorkerThread()
{
    _tournamentModelsThread->terminate();
    _tournamentModelsThread->wait();
}

void ApplicationInterface::stopPlayerModelsWorkerThread()
{
    _playerModelsThread->terminate();
    _playerModelsThread->wait();
}

AbstractGameController *ApplicationInterface::gameController() const
{
    return _gameController;
}

IDefaultGameBuilder *ApplicationInterface::controllerBuilder() const
{
    return _controllerBuilder;
}

AbstractPlayerModelsContext *ApplicationInterface::playerModelsContext() const
{
    return _playerModelsContext;
}

ApplicationInterface *ApplicationInterface::setPlayerModelsContext(AbstractPlayerModelsContext *playerModelsContext)
{
    _playerModelsContext = playerModelsContext;
    return this;
}

IDefaultGameBuilder *ApplicationInterface::controllerBuilder()
{
    return _controllerBuilder;
}

ApplicationInterface *ApplicationInterface::setControllerBuilder(IDefaultGameBuilder *builder)
{
    _controllerBuilder = builder;
    return this;
}

AbstractTournamentModelsContext *ApplicationInterface::tournamentsModelContext() const
{
    return _tournamentModelsContext;
}

ApplicationInterface *ApplicationInterface::setTournamentsModelContext(AbstractTournamentModelsContext *tournamentsModelContext)
{
    _tournamentModelsContext = tournamentsModelContext;
    return this;
}
