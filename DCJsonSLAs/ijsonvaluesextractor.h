#ifndef IJSONVALUESEXTRACTOR_H
#define IJSONVALUESEXTRACTOR_H

#include <qjsondocument.h>
#include <qjsonobject.h>
class IJsonValuesExtractor
{
public:
    virtual int toInt(const QJsonObject &obj, const QString &key) const = 0;
    virtual QString toString(const QJsonObject &obj, const QString &key) const = 0;
    virtual QUuid toId(const QJsonObject &obj, const QString &key) const = 0;
};
#endif // IJSONVALUESEXTRACTOR_H
