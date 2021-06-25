#ifndef IBYTEARRAYJSONMERGER_H
#define IBYTEARRAYJSONMERGER_H

#include "imergejson.h"
#include <qbytearray.h>

class IByteArrayJsonMerger : public IMergeJson<QByteArray>
{
public:
    virtual void mergeIntoJson(QByteArray &json1, const QByteArray &json2) const = 0;
};

#endif // ICOMBINEJSONBYTEARRAYSERVICE_H
