#ifndef COMBINEDARTSINDEXESANDDARTSPOINTJSON_H
#define COMBINEDARTSINDEXESANDDARTSPOINTJSON_H

#include "icombinejsonbytearrayservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class CombineDartsIndexesAndDartsPointJson : public ICombineJsonByteArray
{
public:
    QByteArray combineJson(const QByteArray &json1, const QByteArray &json2) const override
    {
        auto document1 = QJsonDocument::fromJson(json1);
        auto document2 = QJsonDocument::fromJson(json2);
        auto jsonObject1 = document1.object();
        auto jsonObject2 = document2.object();
        QJsonObject combinedJsonObject;
        combine(combinedJsonObject,jsonObject1);
        combine(combinedJsonObject,jsonObject2);
        auto document = QJsonDocument(combinedJsonObject);
        auto json = document.toJson();
        return json;
    }

private:
    void combine(QJsonObject &object, QJsonObject &addend) const
    {
        auto keys = addend.keys();
        for (const auto &key : keys)
            object[key] = addend.value(key);
    }
};

#endif // COMBINEDARTSINDEXESANDDARTSPOINTJSON_H
