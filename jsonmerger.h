#ifndef JSONMERGEBYBYTEARRAYSERVICE_H
#define JSONMERGEBYBYTEARRAYSERVICE_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class JsonMerger
{
public:
    static QByteArray createJsonFromList(const QVector<QByteArray> &json)
    {
        QByteArray resultingJson;
        for (const auto &json : json)
            resultingJson = mergeJson(resultingJson,json);
        return resultingJson;
    }

private:
    static QByteArray mergeJson(const QByteArray &json1, const QByteArray &json2)
    {
        auto document1 = QJsonDocument::fromJson(json1);
        auto document2 = QJsonDocument::fromJson(json2);
        auto jsonObject1 = document1.object();
        auto jsonObject2 = document2.object();
        QJsonObject combinedJsonObject;
        combine(combinedJsonObject,jsonObject1);
        combine(combinedJsonObject,jsonObject2);
        auto newDocument = QJsonDocument(combinedJsonObject);
        auto json = newDocument.toJson();
        return json;
    }
    static void combine(QJsonObject &object, QJsonObject &addend)
    {
        auto keys = addend.keys();
        for (const auto &key : keys)
            object[key] = addend.value(key);
    }
};

#endif // COMBINEDARTSINDEXESANDDARTSPOINTJSON_H
