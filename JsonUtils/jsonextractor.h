#ifndef JSONEXTRACTOR_H
#define JSONEXTRACTOR_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class JsonExtractor
{
public:
    JsonExtractor(const QByteArray &json)
    {
        auto document = QJsonDocument::fromJson(json);
        if(document.isObject())
            _obj = document.object();
    }
    QJsonObject toObject(const QString &key) const
    {
        auto jsonVal = _obj.value(key);
        if(!jsonVal.isObject())
            return QJsonObject();
        return jsonVal.toObject();
    }
    QJsonArray toArray(const QString &key) const
    {
        auto jsonVal = _obj.value(key);
        if(!jsonVal.isArray())
            return QJsonArray();
        return jsonVal.toArray();
    }
private:
    QJsonObject _obj;
};

#endif // JSONEXTRACTOR_H
