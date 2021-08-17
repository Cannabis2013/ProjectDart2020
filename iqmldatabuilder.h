#ifndef IQMLDATABUILDER_H
#define IQMLDATABUILDER_H

#include <qvector.h>
template<typename T, typename U>
class IQMLDataBuilder
{
public:
    virtual U createData(const T &d) const = 0;
};

#endif // IQMLDATABUILDER_H
