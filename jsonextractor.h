#ifndef JSONEXTRACTOR_H
#define JSONEXTRACTOR_H

#include <qjsonobject.h>
#include <qjsonarray.h>
#include <QJsonDocument>

class JsonExtractor
{
public:
    template<typename TReturnValue>
    TReturnValue extractValue(const QByteArray& json, const QString& key)
    {
        auto document = QJsonDocument::fromJson(json);
        QJsonObject jsonObject;
        if(document.isObject())
            jsonObject = document.object();
        else
            throw "Is not object";
        auto jsonValue = jsonObject.value(key).toVariant();
        TReturnValue typeInferedValue = jsonValue.value<TReturnValue>();
        return typeInferedValue;
    }
    template<typename TReturnValue>
    TReturnValue extractValueFromObjectContainer(const QByteArray& json,
                                           const QString& containerKey,
                                           const QString& key)
    {
        auto document = QJsonDocument::fromJson(json);
        QJsonObject jsonObject;
        if(document.isObject())
            jsonObject = document.object();
        else
            throw "Is not an object";
        auto anotherObjectValue = jsonObject.value(containerKey);
        QJsonObject anotherObject;
        if(anotherObjectValue.isObject())
            anotherObject = anotherObjectValue.toObject();
        else
            throw "Key container is not an object";
        auto jsonValue = anotherObject.value("key");
        auto jsonVariant = jsonValue.toVariant();
        auto typeInferedValue = jsonVariant.value<TReturnValue>();
        return typeInferedValue;
    }
    template<typename TElement>
    QVector<TElement> extractValuesFromArrayContainer(const QByteArray& json,
                                           const QString& containerKey,
                                           const QString& key)
    {
        auto document = QJsonDocument::fromJson(json);
        QJsonObject jsonObject;
        if(document.isObject())
            jsonObject = document.object();
        else
            throw "Is not an object";
        auto anotherArrayValue = jsonObject.value(containerKey);
        QJsonArray anotherObject;
        if(anotherArrayValue.isArray())
            anotherObject = anotherArrayValue.toArray();
        else
            throw "Key container is not an object";
        // TODO: Not implented fully
    }
};

#endif // JSONEXTRACTOR_H
