#include "projectdart.h"


QString ProjectDart::createTournament(const QString &title, const int &legCount, const int &maxPlayers, const int &gameMode, const int &keyPoint)
{
    _dataContext->createTournament(title,maxPlayers,keyPoint,legCount,gameMode);
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

void ProjectDart::addPoint(const int &value)
{
    auto gameStatus = _gameController->processInput(value);
    Q_UNUSED(gameStatus);
    /*
     * Evaluate status to determine further progress
     */
}

void ProjectDart::startGame()
{
}

void ProjectDart::stopGame()
{
}

int ProjectDart::score(const QString &tournament, const QString &player)
{
}

void ProjectDart::assignPlayer(const QString &player, const QString &tournament)
{
}

QString ProjectDart::createPlayer(const QString &firstName, const QString &lastName, const QString &email)
{
}


QStringList ProjectDart::gameModes() const
{

}
