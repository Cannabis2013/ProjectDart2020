#include "playerreport.h"
#include "src/players/models/dartsplayer.h"

#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/servicecollection.h"
#include "src/status/idartsstatus.h"
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>

PlayerReport::PlayerReport(ServiceCollection* services)
    : _services(services)
{
}

QByteArray PlayerReport::report() const
{
        QJsonArray arr;
        auto players = _services->players->all();
        for (const auto& player : players)
                arr << player.jsonObject();
        return QJsonDocument(arr).toJson(QJsonDocument::Compact);
}

QByteArray PlayerReport::playerOne() const
{
        auto players = _services->players->all();
        auto jsonObj = players.first().jsonObject();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

QByteArray PlayerReport::playerTwo() const
{
        auto players = _services->players->all();
        auto jsonObj = players.last().jsonObject();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

QString PlayerReport::currentPlayer() const
{
        QJsonObject jsonObj;
        jsonObj["currentPlayerName"] = _services->playerFetcher->one().name();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

bool PlayerReport::isWinnerFound() const
{
        return _services->status->isWinnerFound();
}

QByteArray PlayerReport::winnerInfo() const
{
        QJsonObject jsonObj;
        auto winner = _services->playerFetcher->winner();
        jsonObj["winnerName"] = winner.name();
        jsonObj["winnerImage"] = winner.winnerImageUrl();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}
