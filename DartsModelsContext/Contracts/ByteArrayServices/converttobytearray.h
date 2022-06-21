#ifndef CONVERTTOBYTEARRAY_H
#define CONVERTTOBYTEARRAY_H
#include <qjsondocument.h>
class ConvertToByteArray
{
public:
    static QByteArray toByteArray(const QJsonObject &json);
};

#endif // CONVERTTOBYTEARRAY_H
