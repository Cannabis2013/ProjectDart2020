#include "projectdart.h"


int ProjectDart::tournamentsCount()
{
}

QString ProjectDart::tournamentIDFromIndex(const int &index)
{
}

int ProjectDart::tournamentMaxPlayers(const QString &id)
{
}

int ProjectDart::tournamentLegsCount(const QString &id)
{
}

int ProjectDart::tournamentPlayersCount(const QString &id)
{
}

int ProjectDart::assignedPlayersCount(const QString &tournament)
{
}

int ProjectDart::playersCount()
{
}

QString ProjectDart::assignedPlayerIDfromIndex(const int &tournamentID, const int &index)
{
}

QString ProjectDart::playerIDFromIndex(const int &index)
{
}

int ProjectDart::playerFirstName(const QString &player)
{
}

int ProjectDart::playerLastName(const QString &player)
{
}

int ProjectDart::playerEmail(const QString &player)
{
}

int ProjectDart::currentGameRoundIndex(const QString &tournament)
{
}

int ProjectDart::currentGameSetIndex(const QString &tournament)
{
}

void ProjectDart::addPoint(const int &value)
{
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


QString ProjectDart::createTournament(const QString &title, const int &legCount, const int &maxPlayers, const int &gameMode)
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
