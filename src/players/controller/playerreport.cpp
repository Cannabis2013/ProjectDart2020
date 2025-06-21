#include "playerreport.h"
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

PlayerReport::PlayerReport(ServiceCollection* services)
    : _services(services)
{
}

QByteArray PlayerReport::report() const
{
    QJsonArray arr;
    auto players = _services->players->all();
    for (const auto &player : players)
        arr << player.jsonObject();
    return QJsonDocument(arr).toJson(QJsonDocument::Compact);
}

QString PlayerReport::current() const
{
    auto playerIndex = _services->indexes->index().playerIndex();
    QJsonObject jsonObj = _services->playerFetcher->get(playerIndex).jsonObject();
    return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

bool PlayerReport::isWinnerFound() const
{
    auto players = _services->players->all();
    for (const auto& player : players) {
        if(player.winner())
            return true;
    }
    return false;
}

QByteArray PlayerReport::winnerInfo() const
{
    QJsonObject jsonObj;
    auto winner = _services->playerFetcher->winner();
    jsonObj["winnerName"] = winner.name();
    jsonObj["winnerImage"] = winner.winnerImageUrl();
    return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

QByteArray PlayerReport::all() const
{
    QJsonArray arr;
    auto players = _services->players->all();
    for (const auto& player : std::as_const(players))
        arr << player.jsonObject();
    return QJsonDocument(arr).toJson(QJsonDocument::Compact);
}
