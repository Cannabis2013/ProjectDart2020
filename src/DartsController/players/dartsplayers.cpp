#include "dartsplayers.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/players/pdcchampions.h"
#include "src/DartsController/players/playersio.h"
#include "src/DartsController/servicecollection.h"
#include <QJsonArray>
#include <QJsonValue>
#include <qjsondocument.h>

DartsPlayers::DartsPlayers(ServiceCollection* services)
    : _services(services)
{
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
        auto playerIndex = _services->indexes->index().playerIndex();
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

QList<DartsPlayer> DartsPlayers::all() const
{
        return _players;
}

bool DartsPlayers::saveState()
{
        return _playersIO->saveToFile(_players);
}
