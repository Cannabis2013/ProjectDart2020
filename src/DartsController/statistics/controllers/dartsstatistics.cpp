#include "dartsstatistics.h"
#include "src/DartsController/input/services/idartsinputsfilter.h"
#include "src/DartsController/players/models/dartsplayer.h"
#include "src/DartsController/players/persistences/idartsplayers.h"
#include "src/DartsController/scores/persistence/idartsscores.h"
#include "src/DartsController/scores/services/iscorescalculator.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/statistics/services/iinputstatistics.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QList>

DartsStatistics::DartsStatistics(ServiceCollection* services)
    : _services(services)
{
}

QByteArray DartsStatistics::playerOne() const
{
        auto players = _services->players->all();
        auto name = players.first().name();
        auto obj = playerReport(name);
        return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

QByteArray DartsStatistics::playerTwo() const
{
        auto players = _services->players->all();
        auto name = players.last().name();
        auto obj = playerReport(name);
        return QJsonDocument(obj).toJson(QJsonDocument::Compact);
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
