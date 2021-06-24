#ifndef ICOMBINEJSONBYTEARRAYSERVICE_H
#define ICOMBINEJSONBYTEARRAYSERVICE_H

#include "icombinejsonservice.h"
#include <qbytearray.h>

class ICombineJsonByteArray : public ICombineJsonService<QByteArray>
{
public:
    virtual void addToJson(QByteArray &json1, const QByteArray &json2) const = 0;
};

#endif // ICOMBINEJSONBYTEARRAYSERVICE_H
