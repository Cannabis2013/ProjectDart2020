#include "dartsplayers.h"
#include <QJsonArray>
#include <QJsonValue>
#include <qjsondocument.h>

DartsPlayers::DartsPlayers(IDartsIndexes* indexes)
{
        _indexes = indexes;
        _playersIO = new PlayersIO("players.dat");
}

void DartsPlayers::init(const QList<DartsPlayer>& players)
{
        _players = players;
}

void DartsPlayers::initFromFile()
{
        _players = _playersIO->initFromFile();
}

void DartsPlayers::reset()
{
        for (auto& player : _players)
                player.setWinner(false);
}

DartsPlayer& DartsPlayers::player(const int& index)
{
        return _players[index];
}

DartsPlayer& DartsPlayers::player(const QString& name)
{
        for (auto& player : _players) {
                if (player.name() == name)
                        return player;
        }
        throw new std::invalid_argument("NOT FOUND");
}

DartsPlayer& DartsPlayers::player()
{
        auto playerIndex = _indexes->index().playerIndex();
        return _players[playerIndex];
}

DartsPlayer DartsPlayers::winner() const
{
        for (const auto& player : _players) {
                if (player.winner())
                        return player;
        }
        return DartsPlayer();
}

int DartsPlayers::playersCount() const
{
        return _players.count();
}

const QStringList DartsPlayers::names() const
{
        QStringList names;
        for (const auto& player : _players)
                names << player.name();
        return names;
}

bool DartsPlayers::saveState()
{
        return _playersIO->saveToFile(_players);
}
