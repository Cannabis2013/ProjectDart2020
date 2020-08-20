#include "applicationinterface.h"

ApplicationInterface::ApplicationInterface(AbstractDataContext *dataContext, DefaultControllerBuilderInterface *_builder)
{
    _dataContext = dataContext;
    _gameController = _builder->buildController(GameModes::FirstToPost,ContextMode::LocalContext);
    /*
     * Setup communication between datacontext and controllercontext
     */
    connect(_gameController,&AbstractGameController::sendRequestToContext,_dataContext,&AbstractDataContext::handleRequestFromContext);
    connect(_dataContext,&AbstractDataContext::sendResponseToContext,_gameController,&AbstractGameController::handleResponseFromContext);
    connect(_dataContext,&AbstractDataContext::sendRequestToContext,_gameController,&AbstractGameController::handleRequestFromContext);
    connect(_gameController,&AbstractGameController::sendResponseToContext,_dataContext,&AbstractDataContext::handleResponseFromContext);
    /*
     * UI requests tournament meta information
     */
    connect(this,&ApplicationInterface::sendTournamentMetaRequest,_dataContext,&AbstractDataContext::handleTournamentMetaRequest);
    connect(_dataContext,&AbstractDataContext::sendRequestedMeta,this,&ApplicationInterface::sendTournamentmetaInformation);
    // UI request removal of tournaments from datacontext
    connect(this,&ApplicationInterface::requestDeleteTournaments,_dataContext,&AbstractDataContext::handleDeleteTournamentsRequest);
    // UI request current state of gamecontroller
    connect(this,&ApplicationInterface::requestControllerState,_gameController,&AbstractGameController::handleRequestFromUI);
    // UI request a list of tournaments -> Send a list of tournaments back to UI
    connect(this,&ApplicationInterface::requestTournaments,_dataContext,&AbstractDataContext::handleTournamentsRequest);
    connect(_dataContext,&AbstractDataContext::sendTournament,this,&ApplicationInterface::sendRequestedTournament);
    /*
     * UI request set current tournament
     */
    connect(this,&ApplicationInterface::setCurrentActiveTournament,_gameController,&AbstractGameController::setCurrentTournament);
    // Notify UI regarding context states
    connect(_gameController,&AbstractGameController::transmitResponse,this,&ApplicationInterface::transmitResponse);
    connect(_dataContext,&AbstractDataContext::transmitResponse,this,&ApplicationInterface::transmitResponse);
    // UI needs to populate its scoreboard with keypoint, playernames and player scores
    connect(this,&ApplicationInterface::requestPlayerScores,_dataContext,&AbstractDataContext::handlePlayerScoresRequest);
    connect(_dataContext,&AbstractDataContext::sendCurrentTournamentKeyPoint,this,&ApplicationInterface::sendCurrentTournamentKeyPoint);
    connect(_dataContext,&AbstractDataContext::sendAssignedPlayerName,this,&ApplicationInterface::sendAssignedPlayerName);
    connect(_dataContext,&AbstractDataContext::sendPlayerScore,this,&ApplicationInterface::sendPlayerScore);
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
    // Request start game -> Start game
    connect(this,&ApplicationInterface::startGame,_gameController,&AbstractGameController::start);
    // Request stop game -> Stop game
    connect(this,&ApplicationInterface::stopGame,_gameController,&AbstractGameController::stop);
    // Request restart gane -> Restart game
    connect(this,&ApplicationInterface::requestRestart,_gameController,&AbstractGameController::restartGame);
    // Propagate UI input to controllercontext
    connect(this,&ApplicationInterface::sendPoint,_gameController,&AbstractGameController::handleAndProcessUserInput);
    // Undo/Redo functionality
    connect(this,&ApplicationInterface::requestUndo,_gameController,&AbstractGameController::undoTurn);
    connect(this,&ApplicationInterface::requestRedo,_gameController,&AbstractGameController::redoTurn);
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

void ApplicationInterface::handleCreateTournament(const QString &title,
                                                  const int &numberOfThrows,
                                                  const int &gameMode,
                                                  const int &winCondition,
                                                  const int &keyPoint,
                                                  const QVariantList &playerIndexes)
{
    emit sendTournamentCandidate(title,numberOfThrows,gameMode,winCondition,keyPoint,playerIndexes);
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
    emit requestRestart();
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

void ApplicationInterface::handleDeleteTournamentsRequest(const QVariantList &indexes)
{
    emit requestDeleteTournaments(indexes);
}

void ApplicationInterface::handleTournamentMetaRequest()
{
    emit sendTournamentMetaRequest();
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
    else if(gameMode == printVariable(RoundLimit))
        return RoundLimit;
    else if(gameMode == printVariable(Circular))
        return Circular;
    else
        return -1;
}
