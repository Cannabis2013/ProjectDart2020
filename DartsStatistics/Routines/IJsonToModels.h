#ifndef IJSONTOMODELS_H
#define IJSONTOMODELS_H
class QByteArray;
template<typename T> class QVector;
template<typename TModel> class IJsonToModels
{
public:
    typedef TModel Model;
    typedef QVector<Model> Models;
    typedef QByteArray ByteArray;
    virtual Models convert(const ByteArray &ba) const = 0;
};

#endif // IJSONTOPLAYERS_H
