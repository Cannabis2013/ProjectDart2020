#ifndef ICREATEJSONFROM_H
#define ICREATEJSONFROM_H

#include <qbytearray.h>

template<typename TModel, typename TJson = QByteArray>
class ICreateJsonFrom
{
public:
    virtual TJson createJson(TModel) const = 0;
};

#endif // ICREATEJSONFROMMODEL_H
