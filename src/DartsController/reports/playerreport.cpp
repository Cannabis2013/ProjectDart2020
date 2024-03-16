#include "playerreport.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>

#include "src/DartsController/servicecollection.h"

PlayerReport::PlayerReport(ServiceCollection* services)
    : _players(services->players)
{
}

QByteArray PlayerReport::report() const
{
        QJsonArray arr;
        auto players = _players->all();
        for (const auto& player : players)
                arr << player.jsonObject();
        return QJsonDocument(arr).toJson(QJsonDocument::Compact);
}

QByteArray PlayerReport::playerOne() const
{
        auto players = _players->all();
        auto jsonObj = players.at(0).jsonObject();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

QByteArray PlayerReport::playerTwo() const
{
        auto players = _players->all();
        auto jsonObj = players.at(1).jsonObject();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}
