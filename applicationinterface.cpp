#include "applicationinterface.h"

ApplicationInterface::ApplicationInterface(AbstractDataContext *dataContext, DefaultControllerBuilderInterface *_builder)
{
    _dataContext = dataContext;
    _gameController = _builder->buildController(GameModes::FirstToPost,ContextMode::LocalContext);

    // UI request current state of gamecontroller
    connect(this,&ApplicationInterface::requestControllerState,_gameController,&AbstractGameController::handleControllerStateRequest);
    // UI request a list of tournaments -> Send a list of tournaments back to UI
    connect(this,&ApplicationInterface::requestTournaments,_dataContext,&AbstractDataContext::sendRequestedTournaments);
    connect(_dataContext,&AbstractDataContext::sendTournament,this,&ApplicationInterface::sendRequestedTournament);
    // Set current tournament -> Initialize controller indexes
    connect(this,&ApplicationInterface::setCurrentActiveTournament,_dataContext,&AbstractDataContext::handleSetCurrentTournament);
    connect(_dataContext,&AbstractDataContext::sendInitialControllerValues,_gameController,&AbstractGameController::handleInitialValuesFromDataContext);
    connect(_gameController,&AbstractGameController::requestInitialIndexes,_dataContext,&AbstractDataContext::handleInitialIndexesRequest);
    connect(_dataContext,&AbstractDataContext::sendInitialControllerIndexes,_gameController,&AbstractGameController::handleIndexesFromDatacontext);
    // Notify UI regarding context states
    connect(_gameController,&AbstractGameController::sendStatus,this,&ApplicationInterface::sendStatus);
    connect(_dataContext,&AbstractDataContext::sendStatus,this,&ApplicationInterface::sendStatus);
    // Game UI needs to be updated. The following connection until next comment ensures that
    connect(this,&ApplicationInterface::requestPlayerScores,_gameController,&AbstractGameController::handleCurrentTournamentRequest);
    connect(_gameController,&AbstractGameController::sendCurrentTournament,_dataContext,&AbstractDataContext::handleSendPlayerScoresRequest);
    connect(_dataContext,&AbstractDataContext::sendCurrentTournamentKeyPoint,this,&ApplicationInterface::sendCurrentTournamentKeyPoint);
    connect(_dataContext,&AbstractDataContext::sendAssignedPlayerName,this,&ApplicationInterface::sendAssignedPlayerName);
    connect(_dataContext,&AbstractDataContext::sendPlayerScore,this,&ApplicationInterface::sendPlayerScore);
    // Datacontext has to notify controller about its state
    connect(_gameController,&AbstractGameController::requestContextStatusUpdate,_dataContext,&AbstractDataContext::handleControllerStatusRequest);
    connect(_dataContext,&AbstractDataContext::sendContextStatus,_gameController,&AbstractGameController::handleReplyFromDataContext);
    // UI request creation of a new tournament
    connect(this,&ApplicationInterface::sendTournamentCandidate,_dataContext,&AbstractDataContext::createTournament);
    // UI request creation of a new player
    connect(this,&ApplicationInterface::requestCreatePlayer,_dataContext,&AbstractDataContext::createPlayer);
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
    // User point input
    connect(this,&ApplicationInterface::sendPoint,_gameController,&AbstractGameController::handleInput);
    connect(_gameController,&AbstractGameController::requestScoreCalculation,_dataContext,&AbstractDataContext::handleScoreCalculationRequest);
    connect(_dataContext,&AbstractDataContext::sendCalculatedScore,_gameController,&AbstractGameController::processInput);
    // Send point to datacontext
    connect(_gameController,&AbstractGameController::sendPoint,_dataContext,&AbstractDataContext::addScore);
    // Undo/Redo functionality
    connect(this,&ApplicationInterface::requestUndo,_gameController,&AbstractGameController::undoTurn);
    connect(this,&ApplicationInterface::requestRedo,_gameController,&AbstractGameController::redoTurn);
    connect(_gameController,&AbstractGameController::requestSetScoreHint,_dataContext,&AbstractDataContext::setScoreHint);
    connect(_gameController,&AbstractGameController::removeScore,this,&ApplicationInterface::removeScore);
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
                                            const int &gameMode,
                                            const int &keyPoint,
                                            const QVariantList &playerIndexes)
{
    emit sendTournamentCandidate(title,numberOfThrows,gameMode,keyPoint,playerIndexes);
}

void ApplicationInterface::createPlayer(const QString &userName, const QString &email)
{
    emit requestCreatePlayer(userName,email);
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

void ApplicationInterface::handleUserInput(const int &point)
{
    emit sendPoint(point);
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
