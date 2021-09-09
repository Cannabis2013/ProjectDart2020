#ifndef JSONVALUESEXTRACTOR_H
#define JSONVALUESEXTRACTOR_H

#include "ijsonvaluesextractor.h"
class JsonValuesExtractor : public IJsonValuesExtractor
{
public:
    int toInt(const QJsonObject &obj, const QString &key) const override
    {
        auto value = obj[key];
        if(value != QJsonValue::Undefined)
            return value.toInt();
        return -1;
    }
    QString toString(const QJsonObject &obj, const QString &key) const override
    {
        auto value = obj[key];
        if(value != QJsonValue::Undefined)
            return value.toString();
        return QString();
    }
    QUuid toId(const QJsonObject &obj, const QString &key) const override
    {
        auto value = obj[key];
        if(value != QJsonValue::Undefined)
            return QUuid::fromString(value.toString());
        return QUuid();
    }
};



#endif // JSONVALUESEXTRACTOR_H
