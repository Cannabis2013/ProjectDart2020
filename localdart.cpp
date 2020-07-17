#include "localdart.h"

void LocalDart::read()
{
}

void LocalDart::write()
{

}

void LocalDart::createTournament(const QString &title, const int &numberOfThrows, const int &maxPlayers, const int &gameMode, const int &keyPoint)
{
    if(dataContext() == nullptr)
    {
        emit sendStatus(Status::ContextNotInitialized,{});
        return;
    }
    auto tournamentID = dataContext()->createTournament(title,maxPlayers,keyPoint,numberOfThrows,gameMode).toString();
    emit sendStatus(Status::Success,{tournamentID});
}

int LocalDart::tournamentsCount()
{
    auto count = dataContext()->tournamentsCount();

    return count;
}

QString LocalDart::tournamentIDFromIndex(const int &index)
{
    auto tournaments = dataContext()->tournaments();
    if(index < 0 || index >= tournaments.count())
        return "";
    auto id = tournaments.at(index);
    return id.toString();
}

int LocalDart::tournamentMaxPlayers(const QString &id)
{
    auto stringID = QUuid::fromString(id);
    auto maxPlayers = dataContext()->tournamentMaximumAllowedPlayers(stringID);

    return maxPlayers;
}

int LocalDart::tournamentLegsCount(const QString &id)
{
    auto stringID = QUuid::fromString(id);

    auto legsCount = dataContext()->tournamentNumberOfThrows(stringID);

    return legsCount;
}

int LocalDart::tournamentPlayersCount(const QString &id)
{
    auto stringID = QUuid::fromString(id);
    QList<QUuid> allPlayers;
    try {
        allPlayers = dataContext()->tournamentAssignedPlayers(stringID);
    } catch (const char *msg) {
        return -1;
    }

    auto playersCount = allPlayers.count();

    return playersCount;
}

QString LocalDart::tournamentTitle(const QString &id)
{
    auto title = dataContext()->tournamentTitle(QUuid::fromString(id));

    return title;
}

int LocalDart::tournamentKeyPoint(const QString &id)
{
    auto keyPoint = dataContext()->tournamentKeyPoint(QUuid::fromString(id));

    return keyPoint;
}

int LocalDart::pointValue(const QString &point) const
{
    auto pointID = QUuid::fromString(point);
    auto value = dataContext()->pointValue(pointID);
    return value;
}

int LocalDart::pointValue(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex) const
{
    QUuid pointID;
    try {
        pointID = dataContext()->playerPoint(QUuid::fromString(tournament),
                                            QUuid::fromString(player),
                                            roundIndex,
                                            legIndex,
                                            DisplayHint);
    } catch (const char *msg) {
        return -1;
    }
    auto pVal = dataContext()->pointValue(pointID);
    return pVal;
}

int LocalDart::playersCount()
{
    auto players = playerContext()->players();

    auto count = players.count();

    return count;
}

QString LocalDart::assignedPlayerIDfromIndex(const QString &tournamentID, const int &index)
{
    auto tournament = QUuid::fromString(tournamentID);

    auto players = dataContext()->tournamentAssignedPlayers(tournament);

    auto assignedPlayerID = players.at(index);

    return assignedPlayerID.toString();
}

QString LocalDart::playerIDFromIndex(const int &index)
{
    auto players = playerContext()->players();
    if(index < 0 || index >= players.count())
        return "";
    auto playerID = players.at(index);
    return playerID.toString();
}

QString LocalDart::playerFullName(const QString &player)
{
    auto fullName = playerContext()->playerFullName(QUuid::fromString(player));
    return fullName;
}

QString LocalDart::playerIDFromFullName(const QString &name)
{
    auto playerID = playerContext()->playerIDFromFullName(name);
    return playerID.toString();
}

QString LocalDart::playerFirstName(const QString &player)
{
    auto playerID = QUuid::fromString(player);

    auto firstName = playerContext()->playerFirstName(playerID);

    return firstName;
}

QString LocalDart::playerLastName(const QString &player)
{
    auto playerID = QUuid::fromString(player);

    auto lastName = playerContext()->playerLastName(playerID);

    return lastName;
}

QString LocalDart::playerEmail(const QString &player)
{
    auto playerID = QUuid::fromString(player);

    auto eMail = playerContext()->playerEMail(playerID);

    return eMail;
}

QString LocalDart::resetTournament(const QString &tournament)
{
    auto gameMode = dataContext()->tournamentGameMode(QUuid::fromString(tournament));
    dataContext()->removeTournamentModels(tournament);
    setGameController(controllerBuilder()->buildController(gameMode,0x4));
    gameController()->setDataContext(dataContext());
    return currentActiveTournamentID();

}


QString LocalDart::currentActiveTournamentID()
{
    auto tournamentID = gameController()->currentTournamentID();
    if(tournamentID == QUuid())
        return "";
    return tournamentID.toString();
}

void LocalDart::setCurrentActiveTournament(const int &index)
{
    QUuid tournament;
    try {
        tournament = dataContext()->tournamentIDFromIndex(index);
    }  catch (const char *msg) {
        emit sendStatus(Status::ModelNotFound,{});
        return;
    }
    auto gameMode = dataContext()->tournamentGameMode(tournament);

    if(gameMode == GameModes::FirstToPost && gameController() == nullptr){
       setGameController(controllerBuilder()->buildController(gameMode,0x4));
    }
    if(dataContext() == nullptr)
    {
        emit sendStatus(Status::ContextNotInitialized,{});
        return;
    }
    if(gameController() == nullptr)
    {
        emit sendStatus(Status::ContextNotInitialized,{});
        return;
    }
    if(dataContext() == nullptr)
    {
        emit sendStatus(Status::ContextNotInitialized,{});
        return;
    }
    if(gameController()->dataContext() == nullptr)
        gameController()->setDataContext(dataContext());
    auto playersCount = dataContext()->tournamentAssignedPlayers(tournament).count();
    if(playersCount == 0)
    {
        emit sendStatus(Status::NoPlayersAssigned,{});
        return;
    }
    gameController()->setCurrentTournament(tournament);
    emit sendStatus(Status::Success,{});
}

void LocalDart::requestPlayerDetails()
{
    auto count = playerContext()->playersCount();
    for (int i = 0; i < count; ++i) {
        auto playerID = playerContext()->playerIDFromIndex(i);
        auto firstName = playerContext()->playerFirstName(playerID);
        auto lastName = playerContext()->playerLastName(playerID);
        auto mail = playerContext()->playerEMail(playerID);

        emit sendPlayerDetails(firstName,lastName,mail);
    }
}

QString LocalDart::currentActivePlayerFullName()
{
    if(gameController() == nullptr)
        return "";
    auto playerID =gameController()->currentActivePlayer();
    if(playerContext() == nullptr)
        return "";
    auto fullName =playerContext()->playerFullName(playerID);
    return fullName;
}

QString LocalDart::currentPlayerPoint(const int &hint)
{
    try {
        auto currentTournamentID =  currentActiveTournamentID();
        auto currentPlayerID = gameController()->currentActivePlayer().toString();
        auto currentRoundIndex = currentGameRoundIndex();
        auto currentLegIndex = currentGameLegIndex();
        auto currentPointID = dataContext()->playerPoint(currentTournamentID,currentPlayerID,currentRoundIndex,currentLegIndex, hint);
        return currentPointID.toString();
    } catch (const char *msg) {
        return "";
    }
}

int LocalDart::currentGameRoundIndex()
{
    if(gameController() == nullptr)
        return Status::ContextNotInitialized;
    auto currentRoundIndex = gameController()->currentRoundIndex();
    return currentRoundIndex;
}

int LocalDart::currentGameSetIndex()
{
    if(gameController() == nullptr)
        return Status::ContextNotInitialized;
    auto currentSetIndex = gameController()->currentSetIndex();
    return currentSetIndex;
}

int LocalDart::currentGameLegIndex()
{
    auto currentLegIndex = gameController()->currentLegIndex();
    return currentLegIndex;
}

int LocalDart::addPoint(const int &value)
{
    if(gameController() == nullptr)
    {
        emit sendStatus(Status::ContextNotInitialized,{});
        return Status::ContextNotInitialized;
    }
    auto gameStatus = gameController()->processInput(value);
    return gameStatus;
}

int LocalDart::startGame()
{
    if(gameController() == nullptr)
        return Status::ContextNotInitialized;
    auto controllerStatus = gameController()->start();
    emit sendStatus(controllerStatus,{});


    return controllerStatus;
}

int LocalDart::stopGame()
{
    if(gameController() == nullptr)
        return Status::ContextNotInitialized;
    gameController()->stop();
    auto status = gameController()->status();
    return status;
}

int LocalDart::undoTurn()
{
    try {
        gameController()->undoTurn();
        auto currentPointID = currentPlayerPoint();
        dataContext()->setScoreHint(currentPointID,HiddenHint);
    } catch (const char *msg) {
        return Status::UnSuccess;
    }
    return Status::Success;
}

int LocalDart::redoTurn()
{
    QUuid id;
    try {
        auto currentPointID = currentPlayerPoint(allHints);
        id = gameController()->redoTurn();
        dataContext()->setScoreHint(currentPointID,DisplayHint);
    } catch (const char *msg) {
        return Status::UnSuccess;
    }
    return Status::Success;
}

bool LocalDart::undoPossible()
{
    return gameController()->canUndoTurn();
}

bool LocalDart::redoPossible()
{
    return gameController()->canRedoTurn();
}

void LocalDart::handleStatusRequest()
{
    if(gameController() == nullptr)
    {
        emit sendStatus(Status::ContextNotInitialized,{"Gamecontroller not initialized"});
        return;
    }
    auto gameStatus = gameController()->status();
    auto currentPlayerId = gameController()->currentActivePlayer();
    auto playerName = playerContext()->playerFullName(currentPlayerId);
    emit sendStatus(gameStatus,{playerName});
}

int LocalDart::score(const QString &player)
{
    if(playerContext() == nullptr)
        return -1;
    if(gameController() == nullptr)
        return -1;
    auto playerID = playerContext()->playerIDFromFullName(player);
    auto score = gameController()->score(playerID);
    return score;
}

void LocalDart::handleScoreBoardRequest()
{
    if(gameController() == nullptr)
    {
        emit sendStatus(Status::ModelNotFound,{});
        return;
    }

    auto currentTournamentID = gameController()->currentTournamentID();
    auto currentGameMode = dataContext()->tournamentGameMode(currentTournamentID);
    auto keyPoint = dataContext()->tournamentKeyPoint(currentTournamentID);
    emit sendCurrentTournamentKeyPoint(keyPoint);
    auto numberOfThrows = dataContext()->tournamentNumberOfThrows(currentTournamentID);
    auto assignedPlayersID = dataContext()->tournamentAssignedPlayers(currentTournamentID);
    for (auto assignedPlayerID : assignedPlayersID) {
        auto roundIndex = 1;
        auto throwIndex = 0;
        auto playerName = playerContext()->playerFullName(assignedPlayerID);
        emit sendAssignedPlayerName(playerName);
        if(currentGameMode == GameModes::FirstToPost)
            emit sendPlayerScore(playerName,keyPoint);
        while (1)
        {
            QUuid pointID;
            try {
                pointID = dataContext()->playerPoint(currentTournamentID,
                                                         assignedPlayerID,
                                                         roundIndex,
                                                         throwIndex++,
                                                         DisplayHint);

            }  catch (...) {
                break;
            }

            auto score = dataContext()->playerScore(pointID);
            emit sendPlayerScore(playerName,score);
            if(throwIndex % numberOfThrows == 0)
            {
                throwIndex = 0;
                roundIndex++;
            }
        }
    }
}

void LocalDart::requestTournaments()
{
    auto tournamentsID = dataContext()->tournaments();
    for (auto tournamentID : tournamentsID) {
        auto title = dataContext()->tournamentTitle(tournamentID);
        auto maxPlayers = dataContext()->tournamentMaximumAllowedPlayers(tournamentID);
        auto keyPoint = dataContext()->tournamentKeyPoint(tournamentID);
        auto numberOfThrows = dataContext()->tournamentNumberOfThrows(tournamentID);
        auto assignedPlayersCount = dataContext()->tournamentAssignedPlayers(tournamentID).count();
        auto gameMode = dataContext()->tournamentGameMode(tournamentID);

        emit sendRequestetTournament(title,numberOfThrows,maxPlayers,gameMode,keyPoint,assignedPlayersCount);
    }
}

void LocalDart::assignPlayers(const QVariantList &list, const QString &tournament)
{
    auto tournamentID = QUuid::fromString(tournament);
    for (auto variantItem : list) {
        auto index = variantItem.toInt();
        try {
            auto playerID = playerContext()->playerIDFromIndex(index);
            assignPlayer(playerID,tournamentID);
        }  catch (const char *msg) {
            emit sendStatus(Status::ModelNotFound,{});
            return;
        }

    }

    emit sendStatus(Status::Success,{});
}

void LocalDart::handleGameStatusRecieved(const int &status)
{
    auto currentPlayerID = gameController()->currentActivePlayer();
    auto playerName = playerContext()->playerFullName(currentPlayerID);
    auto roundIndex = gameController()->currentRoundIndex();
    auto canUndo = gameController()->canUndoTurn();
    auto canRedo = gameController()->canRedoTurn();
    auto winnerID = gameController()->determinedWinner();
    auto winnerFullName = playerContext()->playerFullName(winnerID);
    QVariantList arguments = {playerName,roundIndex,canUndo,canRedo, winnerFullName};
    emit sendStatus(status,arguments);

}

void LocalDart::createInitialModels() const
{
    auto kent = playerContext()->playerIDFromFullName("Kent KillerHertz");
    auto martin = playerContext()->playerIDFromFullName("Martin Hansen");
    auto william = playerContext()->playerIDFromFullName("William Worsøe");

    auto count = dataContext()->tournamentsCount();

    for (int i = 0; i < count; ++i) {
        auto tournamentID = dataContext()->tournamentIDFromIndex(i);
        if(i == 0)
        {
            dataContext()->tournamentAddPlayer(tournamentID,kent);
            dataContext()->tournamentAddPlayer(tournamentID,martin);
        }
        else if(i == 1)
        {
            dataContext()->tournamentAddPlayer(tournamentID,kent);
            dataContext()->tournamentAddPlayer(tournamentID,martin);
            dataContext()->tournamentAddPlayer(tournamentID,william);
        }
    }
}

void LocalDart::assignPlayer(const QUuid &player, const QUuid &tournament)
{
    dataContext()->tournamentAddPlayer(tournament,player);
}

void LocalDart::createPlayer(const QString &firstName, const QString &lastName, const QString &email)
{
    playerContext()->createPlayer(firstName,lastName,email);
    emit sendStatus(Status::Success,{});
}


void LocalDart::gameModes() const
{
    QStringList resultingList;

    QString first = printVariable(FirstToPost);
    QString second = printVariable(RoundBased);
    QString third = printVariable(CircularDart);

    resultingList << first << second << third;

    emit sendGameModes(resultingList);
}

void LocalDart::forwardScoreFromDataContext(const QUuid &player, const int &score)
{
    auto playerName = playerContext()->playerFullName(player);
    emit sendPlayerScore(playerName,score);
}

int LocalDart::gameModeFromString(const QString &gameMode) const
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
