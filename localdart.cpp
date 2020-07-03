#include "localdart.h"

LocalDart::LocalDart()
{
    _playerContext = new LocalPlayerContext();
    _dataContext = new LocalDataContext();
    _gameController = new LocalStandardDart();

    _playerContext->setPlayerBuilder(new LocalPlayerBuilder);

    _gameController->setDataContext(_dataContext);
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

    auto legsCount = _dataContext->tournamentNumberOfLegs(stringID);

    return legsCount;
}

int LocalDart::tournamentPlayersCount(const QString &id)
{
    auto stringID = QUuid::fromString(id);

    auto allPlayers = _dataContext->tournamentAssignedPlayers(stringID);

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

int LocalDart::pointValue(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex)
{
    QUuid pointID;
    try {
        pointID = _dataContext->playerPoint(QUuid::fromString(tournament), QUuid::fromString(player),roundIndex,legIndex);
    } catch (...) {
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

    auto playerID = players.at(index);

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

int LocalDart::currentGameRoundIndex()
{
    auto currentRoundIndex = _gameController->currentRoundIndex();

    return currentRoundIndex;
}

int LocalDart::currentGameSetIndex()
{
    auto currentSetIndex = _gameController->currentSetIndex();

    return currentSetIndex;
}

int LocalDart::addPoint(const int &value)
{
    auto gameStatus = _gameController->processInput(value);

    return gameStatus;
}

void LocalDart::startGame()
{
    _gameController->start();
}

void LocalDart::stopGame()
{
    _gameController->stop();
}

QString LocalDart::undoTurn()
{
    try {
        _gameController->undoTurn();
    } catch (const char *msg) {
        throw msg;
    }
}

QString LocalDart::redoTurn()
{
    try {
        _gameController->redoTurn();
    } catch (const char *msg) {
        throw msg;
    }
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

int LocalDart::score(const QString &tournament, const QString &player)
{
    auto playerScore = _dataContext->playerPoints(tournament,player);

    int totalScore = 0;

    for (auto scoreID : playerScore) {
        auto point = _dataContext->pointValue(scoreID);
        totalScore += point;
    }

    return totalScore;
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
        throw std::domain_error("Gamemode not supportet");
}
