#ifndef ICREATEDATAFROM_H
#define ICREATEDATAFROM_H
#include <quuid.h>
#include <qvector.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
template<typename TFrom,typename TData>
class ICreateDataFrom
{
public:
    typedef TFrom FromData;
    typedef TData DataFormat;
    virtual DataFormat create(const QVector<FromData*>& from, DataFormat& to) const = 0;
};
#endif // IJSONBUILDER_H
