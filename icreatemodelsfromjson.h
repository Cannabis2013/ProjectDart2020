#ifndef ICREATEMODELSFROMJSON_H
#define ICREATEMODELSFROMJSON_H

#include "icreatefromjson.h"
#include "iplayerinput.h"
#include <qvector.h>

class ICreateModelsFromJson : public ICreateFromJson<QVector<const IModel<QUuid>*>>
{
public:
    virtual QVector<const IModel<QUuid>*>  create(const QByteArray &json) const override = 0;
};

#endif // ICREATEDARTSPOINTMODELFROMJSON_H
