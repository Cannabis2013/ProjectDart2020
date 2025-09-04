#include "playerfetcher.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/servicecollection.h"

PlayerFetcher::PlayerFetcher(ServiceCollection* services)
    : _services(services)
{
}

DartsPlayer &PlayerFetcher::get(const int &index) {
    auto players = &_services->players->all();
    if (index < 0 || index > players->length())
        throw new std::out_of_range("No player found for current turn index");
    return (*players)[index];
}

DartsPlayer& PlayerFetcher::get(const QString& name)
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


int PlayerFetcher::indexOf(const QString& name) const
{
    auto players = _services->players->all();
    int index = 0;
    for (const auto& player : players) {
        if (player.name() == name)
            return index;
        index++;
    }
    return -1;
}

QStringList PlayerFetcher::names() const {
    QStringList names;
    auto players = _services->players->all();
    for (const auto& player : std::as_const(players))
        names << player.name();
    return names;
}
