#ifndef DBGETINDEXESFROMJSON_H
#define DBGETINDEXESFROMJSON_H
#include "idbgetindexesutility.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class DbGetIndexesFromJson : public IDbGetIndexesUtility
{
public:
    virtual int dbIndexFromJson(const QByteArray &json) const override
    {
        auto obj = createJsonObject(json);
        auto jsonValue = obj.value("index");
        auto index = jsonValue.toInt();
        return index;
    }
    virtual QVector<int> dbIndexesFromJson(const QByteArray &json) const override
    {
        auto obj = createJsonObject(json);
        auto jsonValue = obj.value("indexes");
        auto arr = jsonValue.toArray();
        auto indexes = createIndexesFromArray(arr);
        return indexes;
    }
private:
    QJsonObject createJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        auto obj = document.object();
        return obj;
    }
    QVector<int> createIndexesFromArray(const QJsonArray &arr) const
    {
        QVector<int> indexes;
        for (const auto &jsonValue : arr)
            indexes << jsonValue.toInt();
        return indexes;
    }
};

#endif // DBGETINDEXESFROMJSON_H
