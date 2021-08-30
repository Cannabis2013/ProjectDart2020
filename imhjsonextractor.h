#ifndef IMHJSONEXTRACTOR_H
#define IMHJSONEXTRACTOR_H

#include "ijsonextractor.h"
#include <quuid.h>
class IMHJsonExtractor : public IJsonExtractor<QByteArray,QUuid,QString>
{
public:
    virtual QUuid getIdValueByKey(const QByteArray &json, const QString &key) const = 0;
    virtual QString getStringValueByKey(const QByteArray &json, const QString &key) const = 0;
    virtual int getIntegerValueByKey(const QByteArray &json, const QString &key) const = 0;
};

#endif // IMHJSONEXTRACTOR_H
