#ifndef DCCREATEBYTEARRAY_H
#define DCCREATEBYTEARRAY_H

#include "DartsController/DCJsonSLAs/idccreatebytearray.h"
#include <qjsondocument.h>

class DCCreateByteArray : public IDCCreateByteArray
{
    // ICreateByteArray interface
public:
    virtual QByteArray byteArray(const QJsonObject &obj) const override
    {
        return QJsonDocument(obj).toJson();
    }
    virtual QByteArray byteArray(const QJsonArray &arr) const override
    {
        return QJsonDocument(arr).toJson();
    }
};

#endif // CREATEBYTEARRAY_H
