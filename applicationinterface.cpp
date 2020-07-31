#include "applicationinterface.h"

ApplicationInterface::ApplicationInterface(AbstractDataContext *dataContext, DefaultControllerBuilderInterface *_builder)
{
    _dataContext = dataContext;
    _gameController = _builder->buildController(GameModes::FirstToPost,ContextMode::LocalContext);
    // UI request removal of tournaments from datacontext
    connect(this,&ApplicationInterface::requestDeleteTournaments,_dataContext,&AbstractDataContext::deleteTournamentsFromIndexes);
    // UI request current state of gamecontroller
    connect(this,&ApplicationInterface::requestControllerState,_gameController,&AbstractGameController::handleControllerStateRequest);
    // UI request a list of tournaments -> Send a list of tournaments back to UI
    connect(this,&ApplicationInterface::requestTournaments,_dataContext,&AbstractDataContext::sendRequestedTournaments);
    connect(_dataContext,&AbstractDataContext::sendTournament,this,&ApplicationInterface::sendRequestedTournament);
    /*
     * Set current tournament -> Initialize controller indexes
     * This can also be regarded as the controller initialization state
     */

    /*
     *
     */
    connect(_gameController,&AbstractGameController::sendRequestToDataContext,_dataContext,&AbstractDataContext::handleRequestFromContext);
    connect(_dataContext,&AbstractDataContext::sendResponseToContext,_gameController,&AbstractGameController::handleResponseFromContext);
    /*
     * UI request set current tournament
     */
    connect(this,&ApplicationInterface::setCurrentActiveTournament,_gameController,&AbstractGameController::setCurrentTournament);
    // Notify UI regarding context states
    connect(_gameController,&AbstractGameController::transmitResponse,this,&ApplicationInterface::transmitResponse);
    connect(_dataContext,&AbstractDataContext::transmitResponse,this,&ApplicationInterface::transmitResponse);
    // Game UI needs to be updated. The following connection until next comment ensures that
    connect(this,&ApplicationInterface::requestPlayerScores,_gameController,&AbstractGameController::handleCurrentTournamentRequest);
    connect(_gameController,&AbstractGameController::sendCurrentTournament,_dataContext,&AbstractDataContext::handleSendPlayerScoresRequest);
    connect(_dataContext,&AbstractDataContext::sendCurrentTournamentKeyPoint,this,&ApplicationInterface::sendCurrentTournamentKeyPoint);
    connect(_dataContext,&AbstractDataContext::sendAssignedPlayerName,this,&ApplicationInterface::sendAssignedPlayerName);
    connect(_dataContext,&AbstractDataContext::sendPlayerScore,this,&ApplicationInterface::sendPlayerScore);
    // Datacontext has to notify controller about its state
    connect(_gameController,&AbstractGameController::requestContextStatusUpdate,_dataContext,&AbstractDataContext::handleControllerStatusRequest);
    connect(_dataContext,&AbstractDataContext::sendResponseToContext,_gameController,&AbstractGameController::handleResponseFromContext);
    // UI request creation of a new tournament
    connect(this,&ApplicationInterface::sendTournamentCandidate,_dataContext,&AbstractDataContext::handleCreateTournamentRequest);
    // UI request creation of a new player
    connect(this,&ApplicationInterface::requestCreatePlayer,_dataContext,&AbstractDataContext::handleCreatePlayerRequest);
    // UI request deletion of player
    connect(this,&ApplicationInterface::requestDeletePlayer,_dataContext,&AbstractDataContext::handleDeletePlayerRequest);
    // Request player details
    connect(this,&ApplicationInterface::requestPlayers,_dataContext,&AbstractDataContext::handleSendPlayerDetailsRequest);
    // Send player details to UI
    connect(_dataContext,&AbstractDataContext::sendPlayerDetail,this,&ApplicationInterface::sendPlayerDetail);
    // Send controller indexes to data to add new rounds or sets
    connect(_gameController,&AbstractGameController::sendCurrentIndexes,_dataContext,&AbstractDataContext::updateDataContext);
    // Request start game -> Start game
    connect(this,&ApplicationInterface::startGame,_gameController,&AbstractGameController::start);
    // Request stop game -> Stop game
    connect(this,&ApplicationInterface::stopGame,_gameController,&AbstractGameController::stop);
    // Propagate UI input to controllercontext
    connect(this,&ApplicationInterface::sendPoint,_gameController,&AbstractGameController::handleAndProcessUserInput);
    // Send point to datacontext
    connect(_gameController,&AbstractGameController::sendPoint,_dataContext,&AbstractDataContext::handleAddScoreRequest);
    // Undo/Redo functionality
    connect(this,&ApplicationInterface::requestUndo,_gameController,&AbstractGameController::undoTurn);
    connect(this,&ApplicationInterface::requestRedo,_gameController,&AbstractGameController::redoTurn);
    connect(_gameController,&AbstractGameController::requestSetScoreHint,_dataContext,&AbstractDataContext::setScoreHint);
    connect(_gameController,&AbstractGameController::removeScore,this,&ApplicationInterface::removeScore);
}

ApplicationInterface::~ApplicationInterface()
{
    delete _dataContext;
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

void ApplicationInterface::createTournament(const QString &title,
                                            const int &numberOfThrows,
                                            const QString &gameMode,
                                            const int &keyPoint,
                                            const QVariantList &playerIndexes)
{
    auto mode = gameModeFromString(gameMode);
    emit sendTournamentCandidate(title,numberOfThrows,mode,keyPoint,playerIndexes);
}

void ApplicationInterface::createPlayer(const QString &userName, const QString &email)
{
    emit requestCreatePlayer(userName,email);
}

void ApplicationInterface::handleDeletePlayer(const int &index)
{
    emit requestDeletePlayer(index);
}

void ApplicationInterface::requestPlayerDetails()
{
    emit requestPlayers();
}

void ApplicationInterface::handleSendGameModesRequest() const
{
    QStringList resultingList;

    QString first = printVariable(FirstToPost);
    QString second = printVariable(RoundBased);
    QString third = printVariable(CircularDart);

    resultingList << first << second << third;

    emit sendGameModes(resultingList);
}

void ApplicationInterface::requestStart()
{
    emit startGame();
}

void ApplicationInterface::requestStop()
{
    emit stopGame();
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

void ApplicationInterface::handleDeleTournamentRequest(const QVariantList &indexes)
{
    emit requestDeleteTournaments(indexes);
}

AbstractDataContext *ApplicationInterface::dataContext() const
{
    return _dataContext;
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
    else if(gameMode == printVariable(RoundBased))
        return RoundBased;
    else if(gameMode == printVariable(CircularDart))
        return CircularDart;
    else
        return -1;
}
