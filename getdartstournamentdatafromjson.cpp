#include "getdartstournamentdatafromjson.h"

int GetDartsTournamentDataFromjson::numeric(const Json &json, const String &key) const
{
    auto obj = createJsonObject(json);
    auto numeric = obj.value(key).toInt();
    return numeric;
}

QVector<GetDartsTournamentDataFromjson::Numeric> GetDartsTournamentDataFromjson::numerics(const Json &json, const String &key) const
{
    auto obj = createJsonObject(json);
    auto arr = obj.value(key).toArray();
    return createNumericsFromJsonArray(arr);
}

GetDartsTournamentDataFromjson::Id GetDartsTournamentDataFromjson::id(const Json &json, const String &key) const
{
    auto obj = createJsonObject(json);
    auto stringId = obj.value(key).toString();
    return QUuid::fromString(stringId);
}

QJsonObject GetDartsTournamentDataFromjson::createJsonObject(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto obj = document.object();
    return obj;
}

QVector<GetDartsTournamentDataFromjson::Numeric> GetDartsTournamentDataFromjson::createNumericsFromJsonArray(const QJsonArray &arr) const
{
    QVector<Numeric> values;
    for (const auto &jsonValue : arr)
        values << jsonValue.toInt();
    return values;
}
