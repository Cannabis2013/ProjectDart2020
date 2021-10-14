#include "DartsModelsContext/DMCTournamentServices/extractwinnerinfofromjson.h"

ExtractWinnerInfoFromJson::DataModel ExtractWinnerInfoFromJson::create(const QByteArray &json) const
{
    auto obj = createJsonObject(json);
    auto data = createDataModelFromObject(obj);
    return data;
}

ExtractWinnerInfoFromJson::DataModel ExtractWinnerInfoFromJson::createDataModelFromObject(const QJsonObject &obj) const
{
    DataModel data;
    data.tournamentId = QUuid::fromString(obj.value("tournamentId").toString());;
    data.winnerId = QUuid::fromString(obj.value("playerId").toString());
    data.winnerName = obj.value("playerName").toString("");
    return data;
}

QJsonObject ExtractWinnerInfoFromJson::createJsonObject(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto obj = document.object();
    return obj;
}
