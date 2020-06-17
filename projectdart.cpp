#include "projectdart.h"

ProjectDart::ProjectDart()
{
    _playerContext = new LocalPlayerContext();
    _dataContext = new LocalDataContext();
    _gameController = new LocalStandardDart();
}

void ProjectDart::read()
{

}

void ProjectDart::write()
{

}

QString ProjectDart::createTournament(const QString &title, const int &legCount, const int &maxPlayers, const int &gameMode, const int &keyPoint)
{
    auto tournamentID = _dataContext->createTournament(title,maxPlayers,keyPoint,legCount,gameMode);

    return tournamentID.toString();
}

int ProjectDart::tournamentsCount()
{
    auto count = _dataContext->tournamentsCount();

    return count;
}

QString ProjectDart::tournamentIDFromIndex(const int &index)
{
    auto tournaments = _dataContext->tournaments();

    auto id = tournaments.at(index);

    return id.toString();
}

int ProjectDart::tournamentMaxPlayers(const QString &id)
{
    auto stringID = QUuid::fromString(id);
    auto maxPlayers = _dataContext->tournamentMaximumAllowedPlayers(stringID);

    return maxPlayers;
}

int ProjectDart::tournamentLegsCount(const QString &id)
{
    auto stringID = QUuid::fromString(id);

    auto legsCount = _dataContext->tournamentNumberOfLegs(stringID);

    return legsCount;
}

int ProjectDart::tournamentPlayersCount(const QString &id)
{
    auto stringID = QUuid::fromString(id);

    auto allPlayers = _dataContext->tournamentAssignedPlayers(stringID);

    auto playersCount = allPlayers.count();

    return playersCount;
}

int ProjectDart::playersCount()
{
    auto players = _playerContext->players();

    auto count = players.count();

    return count;
}

QString ProjectDart::assignedPlayerIDfromIndex(const QString &tournamentID, const int &index)
{
    auto tournament = QUuid::fromString(tournamentID);

    auto players = _dataContext->tournamentAssignedPlayers(tournament);

    auto assignedPlayerID = players.at(index);

    return assignedPlayerID.toString();
}

QString ProjectDart::playerIDFromIndex(const int &index)
{
    auto players = _playerContext->players();

    auto playerID = players.at(index);

    return playerID.toString();
}

QString ProjectDart::playerFirstName(const QString &player)
{
    auto playerID = QUuid::fromString(player);

    auto firstName = _playerContext->playerFirstName(playerID);

    return firstName;
}

QString ProjectDart::playerLastName(const QString &player)
{
    auto playerID = QUuid::fromString(player);

    auto lastName = _playerContext->playerLastName(playerID);

    return lastName;
}

QString ProjectDart::playerEmail(const QString &player)
{
    auto playerID = QUuid::fromString(player);

    auto eMail = _playerContext->playerEMail(playerID);

    return eMail;
}

int ProjectDart::currentGameRoundIndex()
{
    auto currentRoundIndex = _gameController->currentRoundIndex();

    return currentRoundIndex;
}

int ProjectDart::currentGameSetIndex()
{
    auto currentSetIndex = _gameController->currentSetIndex();

    return currentSetIndex;
}

int ProjectDart::addPoint(const int &value)
{
    auto gameStatus = _gameController->processInput(value);

    return gameStatus;
}

void ProjectDart::startGame()
{
    _gameController->start();
}

void ProjectDart::stopGame()
{
    _gameController->stop();
}

int ProjectDart::score(const QString &tournament, const QString &player)
{
    auto playerScore = _dataContext->playerPoints(tournament,player);

    int totalScore = 0;

    for (auto scoreID : playerScore) {
        auto point = _dataContext->pointValue(scoreID);
        totalScore += point;
    }

    return totalScore;
}

void ProjectDart::assignPlayer(const QString &player, const QString &tournament)
{
    _dataContext->tournamentAddPlayer(tournament,player);
}

QString ProjectDart::createPlayer(const QString &firstName, const QString &lastName, const QString &email)
{
    auto playerID = _playerContext->createPlayer(firstName,lastName,email);

    return playerID.toString();
}


QStringList ProjectDart::gameModes() const
{
    QStringList resultingList;

    QString first = printVariable(FirstToPost);
    QString second = printVariable(RoundBased);
    QString third = printVariable(CircularDart);

    resultingList << first << second << third;

    return resultingList;
}
