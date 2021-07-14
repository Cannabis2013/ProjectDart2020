#include "getdartstournamentdatafromjson.h"

GetDartsTournamentDataFromjson::Id GetDartsTournamentDataFromjson::tournamentIdFromJson(const Json &json) const
{
    auto obj = createJsonObject(json);
    auto stringId = obj.value("tournamentId").toString();
    return QUuid::fromString(stringId);
}

GetDartsTournamentDataFromjson::Id GetDartsTournamentDataFromjson::winnerIdFromJson(const Json &json) const
{
    auto obj = createJsonObject(json);
    auto stringId = obj.value("winnerId").toString();
    return QUuid::fromString(stringId);
}

QJsonObject GetDartsTournamentDataFromjson::createJsonObject(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto obj = document.object();
    return obj;
}
