#ifndef IDCCREATEBYTEARRAY_H
#define IDCCREATEBYTEARRAY_H

#include <qbytearray.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class IDCCreateByteArray
{
public:
    virtual QByteArray byteArray(const QJsonObject &obj) const = 0;
    virtual QByteArray byteArray(const QJsonArray &arr) const = 0;
};
#endif // ICREATEBYTEARRAY_H
