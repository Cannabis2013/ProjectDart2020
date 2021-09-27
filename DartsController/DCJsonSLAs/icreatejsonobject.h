#ifndef ICREATEJSONOBJECT_H
#define ICREATEJSONOBJECT_H

#include <qjsonobject.h>

class ICreateJsonObject
{
public:
    virtual QJsonObject jsonObject() const = 0;
};
#endif // ICREATEJSONOBJECT_H
