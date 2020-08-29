#include "applicationinterface.h"

ApplicationInterface::ApplicationInterface(AbstractTournamentModelsContext *tournamentModelsContext, AbstractPlayerModelsContext *playerModelsContext, DefaultControllerBuilderInterface *builder)
{

    setObjectName("ApplicationInterface");
    _tournamentsModelContext = tournamentModelsContext;
    _playerModelsContext = playerModelsContext;
    _controllerBuilder = builder;

    _tournamentsModelContext->setObjectName("TournamentModelsContext");
    _playerModelsContext->setObjectName("PlayerModelsContext");

    /*
     * Setup upstream communication between UI and modelcontexts
     */
    connect(tournamentModelsContext,&AbstractTournamentModelsContext::transmitResponse,
            this,&ApplicationInterface::transmitResponse);
    connect(playerModelsContext,&AbstractPlayerModelsContext::transmitResponse,
            this,&ApplicationInterface::transmitResponse);
    connect(_gameController,&AbstractGameController::transmitResponse,
            this,&ApplicationInterface::transmitResponse);
    /*
     * Get all tournaments
     */
    connect(this,&ApplicationInterface::requestTournaments,
            _tournamentsModelContext,&AbstractTournamentModelsContext::handleTransmitTournaments);
    connect(_tournamentsModelContext,&AbstractTournamentModelsContext::sendTournament,
            this,&ApplicationInterface::sendRequestedTournament);
    /*
     * Get all players
     */
    connect(this,&ApplicationInterface::requestPlayers,
            playerModelsContext,&AbstractPlayerModelsContext::handleRequestPlayersDetails);
    connect(playerModelsContext,&AbstractPlayerModelsContext::sendPlayerDetails,
            this,&ApplicationInterface::sendPlayerDetail);
    /*
     * Create tournament
     */
    connect(this,&ApplicationInterface::sendTournamentCandidate,
            playerModelsContext,&AbstractPlayerModelsContext::handleProcessCreatedTournament);
    connect(playerModelsContext,&AbstractPlayerModelsContext::sendProcessedTournamentDetails,
            tournamentModelsContext,&AbstractTournamentModelsContext::assembleAndAddTournament);
    /*
     * Create player
     */
    connect(this,&ApplicationInterface::requestCreatePlayer,
            playerModelsContext,&AbstractPlayerModelsContext::handleCreatePlayerRequest);
    /*
     * Delete tournament
     */
    connect(this,&ApplicationInterface::requestDeleteTournaments,
            tournamentModelsContext,&AbstractTournamentModelsContext::deleteTournament);
    /*
     * Delete players
     */
    connect(this,&ApplicationInterface::requestDeletePlayers,
            playerModelsContext,&AbstractPlayerModelsContext::deletePlayers);
    /*
     * Set current tournament
     */
    connect(this,&ApplicationInterface::setCurrentActiveTournament,
            tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestTournamentDetails);
    connect(tournamentModelsContext,&AbstractTournamentModelsContext::sendTournamentDetails,
            playerModelsContext,&AbstractPlayerModelsContext::processTournamentDetails);
    connect(playerModelsContext,&AbstractPlayerModelsContext::sendTournamentDetails,
            this,&ApplicationInterface::handleTournamentDetailsAndSetController);
    /*
     * Send tournament meta information
     */
    connect(tournamentModelsContext,&AbstractTournamentModelsContext::sendTournamentMeta,
            playerModelsContext,&AbstractPlayerModelsContext::handleAndProcessTournamentMetaData);
    connect(playerModelsContext,&AbstractPlayerModelsContext::sendProcessedTournamentMetaData,
            this,&ApplicationInterface::processRecievedTournamentMetaData);
    /*
     * Send scorepoints
     */
    connect(tournamentModelsContext,&AbstractTournamentModelsContext::sendPlayerScore,
            this,&ApplicationInterface::sendPlayerScore);
}

ApplicationInterface::~ApplicationInterface()
{
    delete _gameController;
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

void ApplicationInterface::handleDeletePlayersRequest(const QVariantList &indexes)
{
    /*
     * TODO: Implement?
     */
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
                                                             const QStringList &assignedPlayerNames)
{
    QVariantList args = {title,gameMode,keyPoint,assignedPlayerNames};
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
        connectInterfaces();
        emit sendTournamentDetails(tournament,
                                   winner,
                                   keyPoint,
                                   terminalKeyCode,
                                   numberOfThrows,
                                   assignedPlayerPairs);
    }
}

void ApplicationInterface::connectInterfaces()
{
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
            _tournamentsModelContext,&AbstractTournamentModelsContext::handleRequestTournamentIndexes);
    connect(_tournamentsModelContext,&AbstractTournamentModelsContext::sendTournamentIndexes,
            _gameController,&AbstractGameController::recieveTournamentIndexes);
    /*
     * Send tournament metadata
     */
    connect(this,&ApplicationInterface::requestTournamentMetaData,
            _gameController,&AbstractGameController::handleRequestForCurrentTournamentMetaData);
    connect(_gameController,&AbstractGameController::requestTournamentMetaData,
            _tournamentsModelContext,&AbstractTournamentModelsContext::handleRequestForTournamentMetaData);
    /*
     * Setup request transmitting playerscores
     */
    connect(this,&ApplicationInterface::requestPlayerScores,
            _gameController,&AbstractGameController::handleRequestForPlayerScores);
    connect(_gameController,&AbstractGameController::sendCurrentTournamentForTransmittingScorePoints,
            _tournamentsModelContext,&AbstractTournamentModelsContext::handleTransmitPlayerScores);
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
            _tournamentsModelContext,&AbstractTournamentModelsContext::handleResetTournament);
    connect(_tournamentsModelContext,&AbstractTournamentModelsContext::tournamentResetSuccess,
            _gameController,&AbstractGameController::handleTournamentResetSuccess);
    /*
     * Add point
     */
    connect(this,&ApplicationInterface::requestControllerState,
            _gameController,&AbstractGameController::handleRequestFromUI);
    connect(this,&ApplicationInterface::sendPoint,
            _gameController,&AbstractGameController::handleAndProcessUserInput);
    connect(_gameController,&AbstractGameController::sendScore,
            _tournamentsModelContext,&AbstractTournamentModelsContext::handleRequestForAddScore);
    connect(_tournamentsModelContext,&AbstractTournamentModelsContext::scoreAddedToDataContext,
            _gameController,&AbstractGameController::handleScoreAddedToDataContext);
    connect(_gameController,&AbstractGameController::requestUpdateContext,
            _tournamentsModelContext,&AbstractTournamentModelsContext::handleRequestUpdateContext);
    connect(_tournamentsModelContext,&AbstractTournamentModelsContext::datacontextUpdated,
            _gameController,&AbstractGameController::handleDataContextUpdated);
    /*
     * Undo/redo
     */
    connect(this,&ApplicationInterface::requestUndo,
            _gameController,&AbstractGameController::undoTurn);
    connect(this,&ApplicationInterface::requestRedo,
            _gameController,&AbstractGameController::redoTurn);
    connect(_gameController,&AbstractGameController::requestSetModelHint,
            _tournamentsModelContext,&AbstractTournamentModelsContext::handleRequestSetScoreHint);
    connect(_tournamentsModelContext,&AbstractTournamentModelsContext::scoreHintUpdated,
            _gameController,&AbstractGameController::handleScoreHintUpdated);
}

AbstractGameController *ApplicationInterface::gameController() const
{
    return _gameController;
}

DefaultControllerBuilderInterface *ApplicationInterface::controllerBuilder() const
{
    return _controllerBuilder;
}

int ApplicationInterface::gameModeFromString(const QString &gameMode) const
{
    if(gameMode == printVariable(FirstToPost))
        return FirstToPost;
    else if(gameMode == printVariable(RoundLimit))
        return RoundLimit;
    else if(gameMode == printVariable(Circular))
        return Circular;
    else
        return -1;
}

AbstractPlayerModelsContext *ApplicationInterface::playerModelsContext() const
{
    return _playerModelsContext;
}

void ApplicationInterface::setPlayerModelsContext(AbstractPlayerModelsContext *playerModelsContext)
{
    _playerModelsContext = playerModelsContext;
}


AbstractTournamentModelsContext *ApplicationInterface::tournamentsModelContext() const
{
    return _tournamentsModelContext;
}

void ApplicationInterface::setTournamentsModelContext(AbstractTournamentModelsContext *tournamentsModelContext)
{
    _tournamentsModelContext = tournamentsModelContext;
}
