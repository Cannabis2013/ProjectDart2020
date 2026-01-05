#include "dartsstatistics.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QList>
#include "src/input/idartsinputsfilter.h"
#include "src/players/idartsplayers.h"
#include "src/servicecollection.h"
#include "src/statistics/istatscalculator.h"
#include "src/turns/dartsturnindex.h"
#include "src/turns/idartsindexes.h"

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

QByteArray DartsStatistics::current() const {
    auto playerIndex = _services->indexes->index().playerIndex();
    auto playerName = _services->players->all().at(playerIndex);
    auto obj = playerReport(playerName);
    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

QByteArray DartsStatistics::player(const int &index) const {
    auto playerName = _services->players->all().at(index);
    auto obj = playerReport(playerName);
    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

QByteArray DartsStatistics::all() const {
    QJsonArray arr;
    for (const auto& playerName : std::as_const(_services->players->all()))
        arr << playerReport(playerName);

    return QJsonDocument(arr).toJson(QJsonDocument::Compact);
}
