#include "converttobytearray.h"
QByteArray ConvertToByteArray::toByteArray(const QJsonObject &json)
{
    auto document = QJsonDocument(json);
    if(!document.isObject())
        return QByteArray();
    return document.toJson();
}
