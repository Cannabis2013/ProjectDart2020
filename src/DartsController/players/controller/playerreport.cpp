#include "playerreport.h"
#include "src/DartsController/players/models/dartsplayer.h"

#include "src/DartsController/players/persistences/idartsplayers.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/status/idartsstatus.h"
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>

PlayerReport::PlayerReport(ServiceCollection* services)
    : _players(services->players)
    , _status(services->status)
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

QString PlayerReport::currentPlayer() const
{
        QJsonObject jsonObj;
        jsonObj["currentPlayerName"] = _players->one().name();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

bool PlayerReport::isWinnerFound() const
{
        return _status->isWinnerFound();
}

QByteArray PlayerReport::winnerInfo() const
{
        QJsonObject jsonObj;
        jsonObj["winnerName"] = _players->winner().name();
        jsonObj["winnerImage"] = _players->winner().winnerImageUrl();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}
