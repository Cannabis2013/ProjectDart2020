#include "localdart.h"

LocalDart::LocalDart()
{
    _playerContext = new LocalPlayerContext();
    _dataContext = new LocalDataContext("MHApps","Dart2020_WIP");

    createInitialModels();
}

void LocalDart::read()
{
}

void LocalDart::write()
{

}

QString LocalDart::createTournament(const QString &title, const int &legCount, const int &maxPlayers, const int &gameMode, const int &keyPoint)
{
    auto tournamentID = _dataContext->createTournament(title,maxPlayers,keyPoint,legCount,gameMode);

    return tournamentID.toString();
}

int LocalDart::tournamentsCount()
{
    auto count = _dataContext->tournamentsCount();

    return count;
}

QString LocalDart::tournamentIDFromIndex(const int &index)
{
    auto tournaments = _dataContext->tournaments();
    if(index < 0 || index >= tournaments.count())
        return "";
    auto id = tournaments.at(index);
    return id.toString();
}

int LocalDart::tournamentMaxPlayers(const QString &id)
{
    auto stringID = QUuid::fromString(id);
    auto maxPlayers = _dataContext->tournamentMaximumAllowedPlayers(stringID);

    return maxPlayers;
}

int LocalDart::tournamentLegsCount(const QString &id)
{
    auto stringID = QUuid::fromString(id);

    auto legsCount = _dataContext->tournamentNumberOfThrows(stringID);

    return legsCount;
}

int LocalDart::tournamentPlayersCount(const QString &id)
{
    auto stringID = QUuid::fromString(id);
    QList<QUuid> allPlayers;
    try {
        allPlayers = _dataContext->tournamentAssignedPlayers(stringID);
    } catch (const char *msg) {
        return -1;
    }

    auto playersCount = allPlayers.count();

    return playersCount;
}

QString LocalDart::tournamentTitle(const QString &id)
{
    auto title = _dataContext->tournamentTitle(QUuid::fromString(id));

    return title;
}

int LocalDart::tournamentKeyPoint(const QString &id)
{
    auto keyPoint = _dataContext->tournamentKeyPoint(QUuid::fromString(id));

    return keyPoint;
}

int LocalDart::pointValue(const QString &point) const
{
    auto pointID = QUuid::fromString(point);
    auto value = _dataContext->pointValue(pointID);
    return value;
}

int LocalDart::pointValue(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex) const
{
    QUuid pointID;
    try {
        pointID = _dataContext->playerPoint(QUuid::fromString(tournament),
                                            QUuid::fromString(player),
                                            roundIndex,
                                            legIndex,
                                            LocalDataContext::DisplayHint);
    } catch (const char *msg) {
        return -1;
    }
    auto pVal = _dataContext->pointValue(pointID);
    return pVal;
}

int LocalDart::playersCount()
{
    auto players = _playerContext->players();

    auto count = players.count();

    return count;
}

QString LocalDart::assignedPlayerIDfromIndex(const QString &tournamentID, const int &index)
{
    auto tournament = QUuid::fromString(tournamentID);

    auto players = _dataContext->tournamentAssignedPlayers(tournament);

    auto assignedPlayerID = players.at(index);

    return assignedPlayerID.toString();
}

QString LocalDart::playerIDFromIndex(const int &index)
{
    auto players = _playerContext->players();
    if(index < 0 || index >= players.count())
        return "";
    auto playerID = players.at(index);
    return playerID.toString();
}

QString LocalDart::playerFullName(const QString &player)
{
    auto fullName = _playerContext->playerFullName(QUuid::fromString(player));
    return fullName;
}

QString LocalDart::playerIDFromFullName(const QString &name)
{
    auto playerID = _playerContext->playerIDFromFullName(name);
    return playerID.toString();
}

QString LocalDart::playerFirstName(const QString &player)
{
    auto playerID = QUuid::fromString(player);

    auto firstName = _playerContext->playerFirstName(playerID);

    return firstName;
}

QString LocalDart::playerLastName(const QString &player)
{
    auto playerID = QUuid::fromString(player);

    auto lastName = _playerContext->playerLastName(playerID);

    return lastName;
}

QString LocalDart::playerEmail(const QString &player)
{
    auto playerID = QUuid::fromString(player);

    auto eMail = _playerContext->playerEMail(playerID);

    return eMail;
}

QString LocalDart::resetTournament(const QString &tournament)
{
    auto gameMode = _dataContext->tournamentGameMode(QUuid::fromString(tournament));
    _dataContext->removeTournamentModels(tournament);
    if(gameMode == GameModes::FirstToPost)
        _gameController = (new LocalFirstToPost)->setPointLogisticInterface(new LogisticContext::PointLogisticManager());
    _gameController->setDataContext(_dataContext);
    return currentActiveTournamentID();

}


QString LocalDart::currentActiveTournamentID()
{
    auto tournamentID = _gameController->currentTournamentID();
    if(tournamentID == QUuid())
        return "";
    return tournamentID.toString();
}

int LocalDart::setCurrentActiveTournament(const int &index)
{
    QUuid tournament;
    try {
        tournament = _dataContext->tournamentIDFromIndex(index);
    }  catch (const char *msg) {
        return Status::ModelNotFound;
    }
    auto gameMode = _dataContext->tournamentGameMode(tournament);
    if(gameMode != GameModes::FirstToPost)
        return Status::UnSuccess;
    else if(gameMode == GameModes::FirstToPost && _gameController == nullptr)
        _gameController = (new LocalFirstToPost())->setPointLogisticInterface(new LogisticContext::PointLogisticManager());
    if(_dataContext == nullptr)
        return Status::ContextNotInitialized;
    if(_gameController == nullptr)
        return Status::ContextNotInitialized;
    if(_dataContext == nullptr)
        return Status::ContextNotInitialized;
    if(_gameController->dataContext() == nullptr)
        _gameController->setDataContext(_dataContext);
    auto playersCount = _dataContext->tournamentAssignedPlayers(tournament).count();
    if(playersCount == 0)
        return Status::NoPlayersAssigned;
    _gameController->setCurrentTournament(tournament);
    return Status::Success;
}

QString LocalDart::currentActivePlayerFullName()
{
    if(_gameController == nullptr)
        return "";
    auto playerID =_gameController->currentActivePlayer();
    if(_playerContext == nullptr)
        return "";
    auto fullName =_playerContext->playerFullName(playerID);
    return fullName;
}

QString LocalDart::currentPlayerPoint(const int &hint)
{
    try {
        auto currentTournamentID =  currentActiveTournamentID();
        auto currentPlayerID = _gameController->currentActivePlayer().toString();
        auto currentRoundIndex = currentGameRoundIndex();
        auto currentLegIndex = currentGameLegIndex();
        auto currentPointID = _dataContext->playerPoint(currentTournamentID,currentPlayerID,currentRoundIndex,currentLegIndex, hint);
        return currentPointID.toString();
    } catch (const char *msg) {
        return "";
    }
}

int LocalDart::currentGameRoundIndex()
{
    if(_gameController == nullptr)
        return Status::ContextNotInitialized;
    auto currentRoundIndex = _gameController->currentRoundIndex();
    return currentRoundIndex;
}

int LocalDart::currentGameSetIndex()
{
    if(_gameController == nullptr)
        return Status::ContextNotInitialized;
    auto currentSetIndex = _gameController->currentSetIndex();
    return currentSetIndex;
}

int LocalDart::currentGameLegIndex()
{
    auto currentLegIndex = _gameController->currentLegIndex();
    return currentLegIndex;
}

int LocalDart::addPoint(const int &value)
{
    if(_gameController == nullptr)
        return Status::ContextNotInitialized;
    auto gameStatus = _gameController->processInput(value);
    return gameStatus;
}

int LocalDart::startGame()
{
    if(_gameController == nullptr)
        return Status::ContextNotInitialized;
    _gameController->start();
    return Status::GameStartet;
}

int LocalDart::stopGame()
{
    if(_gameController == nullptr)
        return Status::ContextNotInitialized;
    _gameController->stop();
    auto status = _gameController->status();
    return status;
}

int LocalDart::undoTurn()
{
    try {
        _gameController->undoTurn();
        auto currentPointID = currentPlayerPoint();
        _dataContext->setScoreHint(currentPointID,LocalDataContext::HiddenHint);
        //_dataContext->removePlayerPointAndRelatives(QUuid::fromString(currentPointID));
    } catch (const char *msg) {
        return Status::UnSuccess;
    }
    return Status::Success;
}

int LocalDart::redoTurn()
{
    QUuid id;
    try {
        auto currentPointID = currentPlayerPoint(LocalDataContext::allHints);
        id = _gameController->redoTurn();
        _dataContext->setScoreHint(currentPointID,LocalDataContext::DisplayHint);
    } catch (const char *msg) {
        return Status::UnSuccess;
    }
    return Status::Success;
}

bool LocalDart::undoPossible()
{
    return _gameController->canUndoTurn();
}

bool LocalDart::redoPossible()
{
    return _gameController->canRedoTurn();
}

int LocalDart::gameStatus()
{
    if(_gameController == nullptr)
        return -1;

    return _gameController->status();
}

int LocalDart::score(const QString &player)
{
    if(_playerContext == nullptr)
        return -1;
    if(_gameController == nullptr)
        return -1;
    auto playerID = _playerContext->playerIDFromFullName(player);
    auto score = _gameController->score(playerID);
    return score;
}

void LocalDart::requestCurrentTournamentPlayerScores()
{
    if(_gameController == nullptr)
    {
        emit notifyStatus(Status::ModelNotFound);
        return;
    }
    auto currentTournamentID = _gameController->currentTournamentID();
    auto numberOfThrows = _dataContext->tournamentNumberOfThrows(currentTournamentID);
    auto assignedPlayersID = _dataContext->tournamentAssignedPlayers(currentTournamentID);
    for (auto assignedPlayerID : assignedPlayersID) {
        auto roundIndex = 1;
        auto throwIndex = 0;
        while (1)
        {
            QUuid pointID;
            try {
                pointID = _dataContext->playerPoint(currentTournamentID,
                                                         assignedPlayerID,
                                                         roundIndex,
                                                         throwIndex,
                                                         LocalDataContext::DisplayHint);

            }  catch (...) {
                break;
            }

            auto score = _dataContext->playerScore(pointID);
            auto playerName = _playerContext->playerFullName(assignedPlayerID);
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
    auto tournamentsID = _dataContext->tournaments();
    for (auto tournamentID : tournamentsID) {
        auto title = _dataContext->tournamentTitle(tournamentID);
        auto maxPlayers = _dataContext->tournamentMaximumAllowedPlayers(tournamentID);
        auto keyPoint = _dataContext->tournamentKeyPoint(tournamentID);
        auto numberOfThrows = _dataContext->tournamentNumberOfThrows(tournamentID);
        auto assignedPlayersCount = _dataContext->tournamentAssignedPlayers(tournamentID).count();
        auto gameMode = _dataContext->tournamentGameMode(tournamentID);

        emit sendRequestetTournament(title,numberOfThrows,maxPlayers,gameMode,keyPoint,assignedPlayersCount);
    }
}

void LocalDart::createInitialModels()
{
    auto kent = _playerContext->playerIDFromFullName("Kent KillerHertz");
    auto martin = _playerContext->playerIDFromFullName("Martin Hansen");
    auto william = _playerContext->playerIDFromFullName("William Worsøe");

    auto count = _dataContext->tournamentsCount();

    for (int i = 0; i < count; ++i) {
        auto tournamentID = _dataContext->tournamentIDFromIndex(i);
        if(i == 0)
        {
            _dataContext->tournamentAddPlayer(tournamentID,kent);
            _dataContext->tournamentAddPlayer(tournamentID,martin);
        }
        else if(i == 1)
        {
            _dataContext->tournamentAddPlayer(tournamentID,kent);
            _dataContext->tournamentAddPlayer(tournamentID,martin);
            _dataContext->tournamentAddPlayer(tournamentID,william);
        }
    }


}

void LocalDart::assignPlayer(const QString &player, const QString &tournament)
{
    _dataContext->tournamentAddPlayer(tournament,player);
}

QString LocalDart::createPlayer(const QString &firstName, const QString &lastName, const QString &email)
{
    auto playerID = _playerContext->createPlayer(firstName,lastName,email);

    return playerID.toString();
}


QStringList LocalDart::gameModes() const
{
    QStringList resultingList;

    QString first = printVariable(FirstToPost);
    QString second = printVariable(RoundBased);
    QString third = printVariable(CircularDart);

    resultingList << first << second << third;

    return resultingList;
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
