#include "dcmetaconverter.h"
#include <qjsonobject.h>
#include <qjsondocument.h>
#include "Models/dcmeta.h"
DCMetaConverter::Meta DCMetaConverter::convert(const ByteArray &byteArray) const
{
    auto json = toJsonObject(byteArray);
    auto meta = toMeta(json);
    return meta;
}

QJsonObject DCMetaConverter::toJsonObject(const QByteArray &byteArray) const
{
    auto document = QJsonDocument::fromJson(byteArray);
    return document.object();
}

DCMeta DCMetaConverter::toMeta(const QJsonObject &json) const
{
    DCMeta meta;
    meta.entryRestricted = json.value("entryRestricted").toBool();
    meta.initRemScore = json.value("initRemScore").toInt();
    meta.playersCount = json.value("assignedPlayersCount").toInt();
    meta.tournamentId = toId(json.value("tournamentId").toString());
    meta.winnerName = json.value("winnerName").toString();
    meta.index.roundIndex = json.value("roundIndex").toInt();
    meta.index.playerIndex = json.value("playerIndex").toInt();
    meta.index.attemptIndex = json.value("attemptIndex").toInt();
    return meta;
}

QUuid DCMetaConverter::toId(const QString &stringId) const
{
    return QUuid::fromString(stringId);
}
