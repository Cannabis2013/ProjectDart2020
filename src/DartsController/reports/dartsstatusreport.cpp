#include "dartsstatusreport.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/status/idartsstatus.h"
#include <QJsonDocument>
#include <QJsonObject>

DartsStatusReport::DartsStatusReport(ServiceCollection* services)
    : _players(services->players)
    , _status(services->status)
{
}

QByteArray DartsStatusReport::report() const
{
        QJsonObject jsonObj;
        jsonObj["currentPlayerName"] = _players->one().name();
        jsonObj["winnerFound"] = _status->isWinnerFound();
        jsonObj["winnerName"] = _players->winner().name();
        jsonObj["winnerImage"] = _players->winner().winnerImageUrl();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

bool DartsStatusReport::isWinnerFound() const
{
        return _status->isWinnerFound();
}
