#ifndef ITOJSON_H
#define ITOJSON_H

#include <qbytearray.h>

template<typename TModel, typename TJson = QByteArray>
class IToJson
{
public:
    virtual TJson toJson(TModel) const = 0;
};

#endif // ICREATEJSONFROMMODEL_H
