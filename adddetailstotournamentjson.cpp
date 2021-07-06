#include "adddetailstotournamentjson.h"

QByteArray AddDetailsToTournamentJson::addPlayerNames(const QByteArray &json, const QVector<QString>& names) const
{
    auto jsonObject = createJsonObject(json);
    auto namesArr = createJsonArray(names);
    jsonObject["assignedPlayerNames"] = namesArr;
    auto newJson = createJson(jsonObject);
    return newJson;
}

QByteArray AddDetailsToTournamentJson::addWinnerName(const QByteArray &json,
                                                                const QString &name) const
{
    auto jsonObject = createJsonObject(json);
    jsonObject["winnerName"] = name;
    auto newJson = createJson(jsonObject);
    return newJson;
}

QJsonObject AddDetailsToTournamentJson::createJsonObject(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto jsonObject = document.object();
    return jsonObject;
}

QByteArray AddDetailsToTournamentJson::createJson(const QJsonObject &jsonObject) const
{
    auto newJSon = QJsonDocument(jsonObject).toJson();
    return newJSon;
}

QJsonArray AddDetailsToTournamentJson::createJsonArray(const QVector<QString> &names) const
{
    QJsonArray namesArr;
    for (const auto& playerName : names)
        namesArr << playerName;
    return namesArr;
}
