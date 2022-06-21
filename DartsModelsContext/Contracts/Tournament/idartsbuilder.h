#ifndef IDARTSBUILDER_H
#define IDARTSBUILDER_H

#include <functional>

class QByteArray;
template<typename T, typename U>
class IDataConverter;
template<typename TModel>

class IDartsBuilder
{
public:
    typedef TModel Model;
    typedef QByteArray ByteArray;
    virtual Model *createModel(const ByteArray &json) const = 0;
    virtual Model *createInitial(std::function<void(Model*)> initializer) const = 0;
};
#endif // ICREATEDARTSPOINTMODELFROMJSON_H
