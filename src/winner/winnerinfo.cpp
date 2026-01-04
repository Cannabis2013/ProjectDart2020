#include "winnerinfo.h"

#include "src/players/persistences/idartsplayers.h"
#include "src/scores/services/idartsremainings.h"
#include "src/servicecollection.h"
#include "src/statistics/services/istatscalculator.h"

#include <QJsonObject>

WinnerInfo::WinnerInfo(ServiceCollection* services)
  : _services(services)
{}

bool WinnerInfo::isWinnerFound() const
{
    auto playerRemaining = 0;

    for (const auto& playerName : std::as_const(_services->players->all())) {
        playerRemaining = _services->scores->fromPlayerName(playerName);
        if (playerRemaining == 0)
            return true;
    }

    return false;
}

QByteArray WinnerInfo::info() const
{
    QJsonObject jsonObj;

    auto playerRemaining = 0;
    auto playerNames = _services->players->all();
    QString playerName;
    for (int i = 0; i < playerNames.length(); i++) {
        playerName = playerNames.at(i);
        playerRemaining = _services->scores->fromPlayerName(playerName);
        if (playerRemaining == 0)
            break;
    }

    jsonObj["name"] = playerName;
    jsonObj["mid"] = _services->inputStatistics->middle(playerName);
    jsonObj["low"] = _services->inputStatistics->lowest(playerName);
    jsonObj["high"] = _services->inputStatistics->highest(playerName);

    return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}
