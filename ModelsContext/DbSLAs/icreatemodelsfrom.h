#ifndef ICREATEMODELSFROM_H
#define ICREATEMODELSFROM_H
#include <quuid.h>
#include <ModelsContext/ModelsSLAs/imodel.h>
template<typename TFrom,typename TModel>
class ICreateModelsFrom
{
public:
    typedef TFrom Data;
    typedef TModel BaseModel;
    virtual QVector<BaseModel*> create(const Data &json) const = 0;
};
#endif // IDARTSCONVERTFROM_H
