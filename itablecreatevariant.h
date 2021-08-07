#ifndef ITABLECREATEVARIANT_H
#define ITABLECREATEVARIANT_H

#include <qvariant.h>
template<typename T, typename U = QVariant>
class ITableCreateVariant
{
public:
    virtual U create(const T &model) const = 0;
};


#endif // ITABLECREATEVARIANT_H
