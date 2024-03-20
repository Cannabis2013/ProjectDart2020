#include "playerfetcher.h"
#include "src/DartsController/players/models/dartsplayer.h"
#include "src/DartsController/players/persistences/idartsplayers.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/turns/models/dartsturnindex.h"
#include "src/DartsController/turns/persistences/idartsindexes.h"

PlayerFetcher::PlayerFetcher(ServiceCollection* services)
    : _services(services)
{
}

DartsPlayer& PlayerFetcher::one()
{
        auto currentTurnIndex = _services->indexes->index().currentTurnIndex();
        auto players = &_services->players->all();
        if (currentTurnIndex < 0 || currentTurnIndex > players->length())
                throw new std::out_of_range("No player found for current turn index");
        return (*players)[currentTurnIndex];
}

DartsPlayer& PlayerFetcher::one(const QString& name)
{
        auto players = &_services->players->all();
        for (auto& player : *players) {
                if (player.name() == name)
                        return player;
        }
        throw new std::invalid_argument("No player with given name found");
}


DartsPlayer PlayerFetcher::winner() const
{
        auto players = _services->players->all();
        for (const auto& player : players) {
                if (player.winner())
                        return player;
        }
        return DartsPlayer();
}
