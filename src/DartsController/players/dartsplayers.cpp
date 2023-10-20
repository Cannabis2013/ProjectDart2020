#include "dartsplayers.h"
#include <QJsonArray>
#include <QJsonValue>
#include <qjsondocument.h>

DartsPlayers::DartsPlayers(IDartsIndexes* indexes)
{
        _indexes = indexes;
        _playersIO = new PlayersIO("players.dat");
}

void DartsPlayers::initPlayers(const QStringList& names)
{
        _players.clear();
        for (const auto& name : names)
                _players << DartsPlayer(name);
}

void DartsPlayers::initPlayers()
{
        _players = _playersIO->initFromFile();
}

QString DartsPlayers::name(int index) const
{
        return _players.at(index).name();
}

QString DartsPlayers::name() const
{
        auto playerIndex = _indexes->index().playerIndex();
        if (playerIndex >= _players.count())
                return QString();
        return _players.at(playerIndex).name();
}

QString DartsPlayers::winnerName() const
{
        for (const auto& player : _players) {
                if (player.winner())
                        return player.name();
        }
        return QString();
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

int DartsPlayers::indexOf(const QString& name) const
{
        for (int index = 0; index < _players.size(); ++index) {
                auto player = _players.at(index);
                if (player.name() == name)
                        return index;
        }
        return -1;
}

void DartsPlayers::declareAsWinner(const QString& name)
{
        for (auto& player : _players) {
                if (player.name() == name)
                        player.setWinner(true);
        }
}
