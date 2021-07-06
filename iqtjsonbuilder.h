#ifndef IQBYTEARRAYJSONBUILDER_H
#define IQBYTEARRAYJSONBUILDER_H

#include "ijsonbuilder.h"
#include <quuid.h>

class IQtJsonBuilder : public IJsonBuilder<QByteArray,QUuid,QString>
{
public:
    virtual JsonFormat createJson(const Id &id, const String &key) const override = 0;
    virtual JsonFormat createJson(const String &string, const String &key) const override = 0;
};

#endif // IQBYTEARRAYJSONBUILDER_H