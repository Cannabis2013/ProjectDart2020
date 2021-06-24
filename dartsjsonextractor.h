#ifndef DARTSJSONEXTRACTOR_H
#define DARTSJSONEXTRACTOR_H

#include "ijsonextractor.h"
#include <qbytearray.h>
#include <quuid.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

class DartsJsonExtractor : public IJsonExtractor<QByteArray,QUuid,QString>
{
public:

    // IJsonExtractor interface
public:
    virtual String getStringValueByKey(const Json &json, const String &key) const override
    {
        auto jsonObject = createObject(json);
        auto value = jsonObject.value(key);
        if(!value.isString())
            return QString();
        auto stringValue = value.toString();
        return stringValue;
    }
    virtual int getIntegerValueByKey(const Json &json, const String &key) const override
    {
        auto jsonObject = createObject(json);
        auto value = jsonObject.value(key);
        auto numericValue = value.toInt();
        return numericValue;
    }
private:
    QJsonObject createObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        auto obj = document.object();
        return obj;
    }
};

#endif // DARTSJSONEXTRACTOR_H
