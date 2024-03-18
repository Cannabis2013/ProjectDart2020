#include "dartsplayers.h"
#include "src/DartsController/players/persistences/playersio.h"
#include "src/DartsController/players/services/pdcchampions.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/turns/models/dartsturnindex.h"
#include "src/DartsController/turns/persistences/idartsindexes.h"
#include <QJsonArray>
#include <QJsonValue>
#include <qjsondocument.h>

DartsPlayers::DartsPlayers(ServiceCollection* services)
    : _services(services)
{
        _playersIO = new PlayersIO();
        _generator = new PdcChampions();
}

void DartsPlayers::init()
{
        _players = _generator->generate();
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
        auto playerIndex = _services->indexes->index().currentTurnIndex();
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
