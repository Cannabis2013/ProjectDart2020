#include "dartsplayers.h"
#include "src/DartsController/players/pdcchampions.h"
#include <QJsonArray>
#include <QJsonValue>
#include <qjsondocument.h>

DartsPlayers::DartsPlayers(IDartsIndexes* indexes)
{
        _indexes = indexes;
        _playersIO = new PlayersIO("players.dat");
}

void DartsPlayers::init()
{
        PdcChampions generator;
        _players = generator.generate();
}

void DartsPlayers::initFromFile()
{
        _players = _playersIO->initFromFile();
}

void DartsPlayers::reset()
{
        PdcChampions generator;
        _players = generator.generate();
}

DartsPlayer& DartsPlayers::one(const int& index)
{
        return _players[index];
}

DartsPlayer& DartsPlayers::one(const QString& name)
{
        for (auto& player : _players) {
                if (player.name() == name)
                        return player;
        }
        throw new std::invalid_argument("NOT FOUND");
}

DartsPlayer& DartsPlayers::one()
{
        auto playerIndex = _indexes->index().playerIndex();
        return _players[playerIndex];
}

QByteArray DartsPlayers::allAsJson() const
{
        QJsonArray arr;
        for (const auto& player : _players)
                arr << player.jsonObject();
        return QJsonDocument(arr).toJson(QJsonDocument::Compact);
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
