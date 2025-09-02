#include "dartsscorescontroller.h"
#include <QJsonArray>
#include <QJsonObject>
#include "src/Finishes/idartsfinishes.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/services/idartsremainings.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

DartsScoresController::DartsScoresController(ServiceCollection* services)
    : _services(services)
{
}

QString DartsScoresController::finishRow() const
{
        auto playerIndex = _services->indexes->index().playerIndex();
        auto playerName = _services->playerFetcher->names().at(playerIndex);
        auto remaining = _services->scores->remaining(playerName);
        return _services->finishes->suggestTargetRow(remaining, 0);
}

int DartsScoresController::current() const {
    auto playerIndex = _services->indexes->index().playerIndex();
    auto player = _services->playerFetcher->get(playerIndex);
    return _services->scores->remaining(player.name());
}

QList<int> DartsScoresController::all() const {
    auto players = _services->players->all();
    QList<int> remainings;
    for (const auto& player : std::as_const(players))
        remainings << _services->scores->remaining(player.name());
    return remainings;
}
