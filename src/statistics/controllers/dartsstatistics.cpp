#include "dartsstatistics.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QList>
#include "src/input/services/idartsinputsfilter.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/iscorescalculator.h"
#include "src/servicecollection.h"
#include "src/statistics/services/istatscalculator.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

DartsStatistics::DartsStatistics(ServiceCollection* services)
    : _services(services)
{
}

QJsonObject DartsStatistics::playerReport(const QString& name) const
{
        QJsonObject jsonObj;
        jsonObj["average"] = _services->inputStatistics->middle(name);
        jsonObj["low"] = _services->inputStatistics->lowest(name);
        jsonObj["high"] = _services->inputStatistics->highest(name);
        jsonObj["throwCount"] = _services->inputsFilter->validCount(name);
        jsonObj["name"] = name;
        return jsonObj;
}

QByteArray DartsStatistics::report() const {
    auto playerIndex = _services->indexes->index().playerIndex();
    auto player = _services->playerFetcher->get(playerIndex);
    auto obj = playerReport(player.name());
    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}
