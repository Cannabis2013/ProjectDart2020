#ifndef IBYTEARRAYJSONMERGER_H
#define IBYTEARRAYJSONMERGER_H

#include "imergejson.h"
#include <qbytearray.h>

class IByteArrayJsonMerger : public IMergeJson<QByteArray>
{
public:
    virtual Json createJsonFromList(const QVector<Json> &json2) const = 0;
};

#endif // ICOMBINEJSONBYTEARRAYSERVICE_H
