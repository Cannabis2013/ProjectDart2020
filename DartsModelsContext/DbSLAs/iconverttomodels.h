#ifndef ICONVERTTOMODELS_H
#define ICONVERTTOMODELS_H
template<typename T>
class QVector;
template<typename TFrom,typename TModel>
class IConvertToModels
{
public:
    typedef TFrom Data;
    typedef TModel Model;
    virtual QVector<Model*> convert(const Data &json) const = 0;
};
#endif // IDARTSCONVERTFROM_H
