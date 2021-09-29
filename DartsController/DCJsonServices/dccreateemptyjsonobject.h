#ifndef DCCREATEEMPTYJSONOBJECT_H
#define DCCREATEEMPTYJSONOBJECT_H

#include <DartsController/DCJsonSLAs/icreatejsonobject.h>

class DCCreateEmptyJsonObject : public ICreateJsonObject
{
public:
    virtual QJsonObject emptyJsonObject() const override
    {
        return QJsonObject();
    }
    virtual QJsonArray emptyJsonArray() const override
    {
        return QJsonArray();
    }
};

#endif // DCCREATEEMPTYJSONOBJECT_H
