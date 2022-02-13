#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H
#include "ModelBuilderSLAs/idcjsontomodel.h"
#include "ModelBuilderSLAs/idcmodeltojson.h"
class QString;
class QByteArray;
template<typename TModel>
class IDCInputBuilder : public IDCJsonToModel<TModel>, public IDCModelToJson<TModel>
{
public:
    typedef TModel Model;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    virtual Model create(const QString &name, const int &remainingScore) const = 0;
    virtual Model create() const = 0;
    virtual Model create(const Json &json, const int &remainingScore) const = 0;
    virtual Model create(const Json &json) const override = 0;
    virtual Json create(const Model &model) const override = 0;
};
#endif // IDCIPTCONVERTER_H
