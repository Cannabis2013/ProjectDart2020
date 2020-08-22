#include "applicationinterface.h"

ApplicationInterface::ApplicationInterface(AbstractTournamentModelsContext *tournamentModelsContext, AbstractPlayerModelsContext *playerModelsContext, DefaultControllerBuilderInterface *builder)
{
    _tournamentsModelContext = tournamentModelsContext;
    _playerModelsContext = playerModelsContext;
    _controllerBuilder = builder;

    /*
     * Get all tournaments
     */
    connect(this,&ApplicationInterface::requestTournaments,
            _tournamentsModelContext,&AbstractTournamentModelsContext::handleTransmitTournaments);
    connect(_tournamentsModelContext,&AbstractTournamentModelsContext::sendTournament,
            this,&ApplicationInterface::sendRequestedTournament);
    /*
     * Set current tournament
     */
    connect(this,&ApplicationInterface::setCurrentActiveTournament,
            tournamentModelsContext,&AbstractTournamentModelsContext::handleTournamentIDFromIndex);
    connect(tournamentModelsContext,&AbstractTournamentModelsContext::sendTournamentIDFromIndex,
            playerModelsContext,&AbstractPlayerModelsContext::assembleAssignedPlayerPairs);
    connect(playerModelsContext,&AbstractPlayerModelsContext::sendPlayerPairs,
            tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestForTournamentDetails);
    connect(tournamentModelsContext,&AbstractTournamentModelsContext::sendTournamentDetails,
            _gameController,&AbstractGameController::recieveTournamentDetails);
    connect(_gameController,&AbstractGameController::requestTournamentIndexes,
            tournamentModelsContext,&AbstractTournamentModelsContext::handleRequestTournamentIndexes);
    connect(tournamentModelsContext,&AbstractTournamentModelsContext::sendTournamentIndexes,
            _gameController,&AbstractGameController::recieveTournamentIndexes);



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
