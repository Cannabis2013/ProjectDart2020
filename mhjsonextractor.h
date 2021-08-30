#ifndef MHJSONEXTRACTOR_H
#define MHJSONEXTRACTOR_H

#include "imhjsonextractor.h"
#include <qbytearray.h>
#include <quuid.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

class MHJsonExtractor : public IMHJsonExtractor
{
public:
    virtual QString getStringValueByKey(const QByteArray &json, const QString &key) const override
    {
        auto jsonObject = createObject(json);
        auto value = jsonObject.value(key);
        if(!value.isString())
            return QString();
        auto stringValue = value.toString();
        return stringValue;
    }
    virtual int getIntegerValueByKey(const QByteArray &json, const QString &key) const override
    {
        auto jsonObject = createObject(json);
        auto value = jsonObject.value(key);
        auto numericValue = value.toInt();
        return numericValue;
    }
    virtual QUuid getIdValueByKey(const QByteArray &json, const QString &key) const override
    {
        auto jsonObject = createObject(json);
        auto value = jsonObject.value(key);
        if(!value.isString())
            return QString();
        auto stringValue = value.toString();
        auto idValue = QUuid(stringValue);
        return idValue;
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
