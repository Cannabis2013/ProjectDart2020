#ifndef DCCREATEEMPTYJSONOBJECT_H
#define DCCREATEEMPTYJSONOBJECT_H

#include <DartsController/DCJsonSLAs/icreatejsonobject.h>

class DCCreateEmptyJsonObject : public ICreateJsonObject
{
public:
    virtual QJsonObject jsonObject() const override
    {
        return QJsonObject();
    }
};

#endif // DCCREATEEMPTYJSONOBJECT_H
