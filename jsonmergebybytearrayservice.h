#ifndef JSONMERGEBYBYTEARRAYSERVICE_H
#define JSONMERGEBYBYTEARRAYSERVICE_H

#include "ibytearrayjsonmerger.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class JsonMergeByByteArrayService : public IByteArrayJsonMerger
{
public:
    Json createJsonFromList(const QVector<Json> &json2) const override
    {
        Json resultingJson;
        for (const auto &json : json2)
            resultingJson = mergeJson(resultingJson,json);
        return resultingJson;
    }

private:
    Json mergeJson(const Json &json1, const Json &json2) const
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
    void combine(QJsonObject &object, QJsonObject &addend) const
    {
        auto keys = addend.keys();
        for (const auto &key : keys)
            object[key] = addend.value(key);
    }
};

#endif // COMBINEDARTSINDEXESANDDARTSPOINTJSON_H
