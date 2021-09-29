#ifndef ICREATEJSONOBJECT_H
#define ICREATEJSONOBJECT_H

#include <qjsonarray.h>
#include <qjsonobject.h>

class ICreateJsonObject
{
public:
    virtual QJsonObject emptyJsonObject() const = 0;
    virtual QJsonArray emptyJsonArray() const = 0;
};
#endif // ICREATEJSONOBJECT_H
