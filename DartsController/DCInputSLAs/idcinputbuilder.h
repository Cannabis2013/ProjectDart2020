#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H
#include <ModelBuilderSLAs/idcmodelbuilder.h>
template<typename TModel, typename TByteArray,typename TJson>
class IDCInputBuilder : public IDCModelBuilder<TModel,TJson>
{
public:
    typedef TModel Model;
    typedef TByteArray ByteArray;
    typedef TJson Json;
    virtual Model create() const = 0;
    virtual Model create(const ByteArray &byteArray, const int &remainingScore = -1) const = 0;
    virtual Model create(const Json &json, const int &remainingScore = -1) const = 0;
    virtual Model create(const Json &json) const override = 0;
    virtual Json create(const Model &byteArray) const = 0;
};
#endif // IDCIPTCONVERTER_H
