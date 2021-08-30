#ifndef IGENEREICJSONBUILDER_H
#define IGENEREICJSONBUILDER_H

#include "ijsonbuilder.h"
#include <quuid.h>

class IGenericJsonBuilder : public IJsonBuilder<QByteArray,QUuid,QString>
{
public:
    virtual JsonFormat createJson(const Id &value, const String &key) const override = 0;
    virtual JsonFormat createJson(const String &value, const String &key) const override = 0;
};

#endif // IQBYTEARRAYJSONBUILDER_H
