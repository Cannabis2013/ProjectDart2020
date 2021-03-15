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
    emit requestMultiThrowPlayerScores();
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
    emit requestCurrentTournamentId();
}

void DartApplication::handlePersistTournamentRequest()
{
    emit requestPersistTournament();
}

void DartApplication::assembleAndConfigureControllerBuilder(const QVector<QUuid> &idAndWinner,
                                                 const QVector<int> &values,
                                                 const QVector<QUuid> &userIds,
                                                 const QVector<QString> &playerNames)
{
    emit assembleFTPController(idAndWinner,
                               values,
                               userIds,
                               playerNames,
                               this,
                               _modelsContext);
}

void DartApplication::setGameController(AbstractGameController *controller)
{
    if(_gameController != nullptr)
        _gameController->disconnect();
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
     * Setup upstream communication between UI and modelcontexts
     */
    connect(_modelsContext,&AbstractModelsContext::transmitResponse,
            this,&DartApplication::transmitResponse);
    /*
     * Get all tournaments
     */
    connect(this,&DartApplication::requestTournaments,
            _modelsContext,&AbstractModelsContext::handleTransmitTournamentData);
    connect(_modelsContext,&AbstractModelsContext::sendTournament,
            this,&DartApplication::sendRequestedTournament);
    connect(_modelsContext,&AbstractModelsContext::lastTournamentTransmitted,
            this,&DartApplication::lastTournamentDetailsTransmitted);
    /*
     * Get all players
     */
    connect(this,&DartApplication::requestPlayers,
            _modelsContext,&AbstractModelsContext::handleRequestPlayersDetails);
    connect(_modelsContext,&AbstractModelsContext::sendPlayerDetails,
            this,&DartApplication::sendPlayerDetail);
    connect(_modelsContext,&AbstractModelsContext::lastPlayerDetailTransmitted,
            this,&DartApplication::lastPlayerDetailsTransmitted);
    /*
     * Create tournament
     */
    connect(this,&DartApplication::sendFTPDetails,
            _modelsContext,&AbstractModelsContext::handleRequestForAddFTPTournament);
    /*
     * Create player
     */
    connect(this,&DartApplication::requestCreatePlayer,
            _modelsContext,&AbstractModelsContext::handleCreatePlayer);
    connect(_modelsContext,&AbstractModelsContext::confirmPlayerCreated,
            this,&DartApplication::playerCreatedSuccess);
    /*
     * Delete tournament
     */
    connect(this,&DartApplication::requestDeleteTournaments,
            _modelsContext,&AbstractModelsContext::handleDeleteTournaments);
    connect(_modelsContext,&AbstractModelsContext::tournamentsDeletedSuccess,
            this,&DartApplication::tournamentsDeletedSuccess);
    /*
     * Delete player{s}
     */
    connect(this,&DartApplication::requestDeletePlayer,
            _modelsContext,&AbstractModelsContext::handleDeletePlayerFromIndex);
    connect(this,&DartApplication::requestDeletePlayers,
            _modelsContext,&AbstractModelsContext::handleDeletePlayersFromIndexes);
    connect(_modelsContext,&AbstractModelsContext::playersDeletedStatus,
            this,&DartApplication::playersDeletedStatus);
    /*
     * Send tournament meta information
     */
    connect(_modelsContext,&AbstractModelsContext::sendTournamentMeta,
            this,&DartApplication::sendFTPTournamentMetaData);
    /*
     * Send scorepoints
     */
    connect(_modelsContext,&AbstractModelsContext::sendPlayerScore,
            this,&DartApplication::sendPlayerScore);
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

DartApplication *DartApplication::setControllerBuilder(ControllerBuilder *builder)
{
    _controllerBuilder = dynamic_cast<AbstractControllerBuilder*>(builder);
    /*
     * Connect interface
     */
    connect(this,&DartApplication::setCurrentActiveTournament,
            _modelsContext,&AbstractModelsContext::handleRequestTournamentGameMode);
    connect(_modelsContext,&AbstractModelsContext::requestAssembleTournament,
            _controllerBuilder,&AbstractControllerBuilder::determineTournamentGameMode);
    connect(_controllerBuilder,&AbstractControllerBuilder::requestFTPDetails,
            _modelsContext,&AbstractModelsContext::handleRequestFTPDetails);
    connect(_modelsContext,&AbstractModelsContext::sendTournamentFTPDetails,
            this,&DartApplication::assembleAndConfigureControllerBuilder);
    connect(this,&DartApplication::assembleFTPController,
            _controllerBuilder,&AbstractControllerBuilder::assembleFTPGameController);
    connect(_controllerBuilder,&AbstractControllerBuilder::sendController,
            this,&DartApplication::setGameController);
    return this;
}
