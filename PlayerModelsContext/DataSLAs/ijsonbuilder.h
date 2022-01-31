#ifndef IDATACONTEXT_H
#define IDATACONTEXT_H
class QByteArray;
template<typename T>
class QVector;
template<typename TModel>
class IJsonBuilder
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    typedef QByteArray ByteArray;
    virtual ByteArray create(const Models &models, ByteArray &data) const = 0;
    virtual ByteArray create(const Models &models) const = 0;
    virtual ByteArray create(Model *model) const = 0;
};
#endif // IDATAADDER_H
