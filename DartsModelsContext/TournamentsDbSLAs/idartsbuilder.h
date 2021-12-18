#ifndef IDARTSBUILDER_H
#define IDARTSBUILDER_H
template<typename T, typename U>
class IDataConverter;
template<typename TBaseModel, typename TSuperModel, typename TJsonFormat, typename TTransitionModel>
class IDartsBuilder
{
public:
    typedef TBaseModel Model;
    typedef TSuperModel SuperModel;
    typedef TJsonFormat JsonFormat;
    typedef TTransitionModel TransitModel;
    virtual SuperModel *createModel(const JsonFormat &json) const = 0;
    virtual TransitModel convert(TSuperModel *tournament) const = 0;
};
#endif // ICREATEDARTSPOINTMODELFROMJSON_H
