#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H
#include <ModelBuilderSLAs/idcmodelconverter.h>
class QByteArray;
template<typename TModel>
class IDCInputBuilder : public IDCModelConverter<TModel>
{
public:
    typedef TModel Model;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    virtual Model create() const = 0;
    virtual Model create(const ByteArray &byteArray, const int &remainingScore = -1) const = 0;
    virtual Model create(const Json &json, const int &remainingScore = -1) const = 0;
    virtual Model create(const Json &json) const override = 0;
    virtual Json create(const Model &byteArray) const = 0;
};
#endif // IDCIPTCONVERTER_H
