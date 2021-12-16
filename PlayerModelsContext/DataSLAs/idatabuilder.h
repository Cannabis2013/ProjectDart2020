#ifndef IDATACONTEXT_H
#define IDATACONTEXT_H
template<typename T>
class QVector;
template<typename TModel, typename TData>
class IDataBuilder
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    typedef TData Data;
    virtual Data create(const Models &models, Data &data) const = 0;
    virtual Data create(const Models &models) const = 0;
};
#endif // IDATAADDER_H
