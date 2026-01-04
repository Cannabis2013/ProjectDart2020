#include "remainingscontroller.h"
#include <QJsonArray>
#include <QJsonObject>
#include "src/players/persistences/idartsplayers.h"
#include "src/scores/services/idartsremainings.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

RemainingsController::RemainingsController(ServiceCollection* services)
    : _services(services)
{}

int RemainingsController::current() const {
    auto playerIndex = _services->indexes->index().playerIndex();
    auto player = _services->players->all().at(playerIndex);
    return _services->scores->fromPlayerName(player);
}

QList<int> RemainingsController::all() const {
    auto playerNames = _services->players->all();
    QList<int> remainings;
    for (const auto& playerName : std::as_const(playerNames))
        remainings << _services->scores->fromPlayerName(playerName);
    return remainings;
}

int RemainingsController::remaining(const QString &playerName) const {
    return _services->scores->fromPlayerName(playerName);
}
