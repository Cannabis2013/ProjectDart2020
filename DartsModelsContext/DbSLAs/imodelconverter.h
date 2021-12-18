#ifndef IMODELCONVERTER_H
#define IMODELCONVERTER_H
template<typename T>
class QVector;
template<typename TFrom,typename TData>
class IModelConverter
{
public:
    typedef TFrom FromData;
    typedef TData DataFormat;
    virtual DataFormat create(const QVector<FromData*>& from, DataFormat& to) const = 0;
};
#endif // IJSONBUILDER_H
