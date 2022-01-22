#ifndef DARTSDBINPUTSTOJSON_H
#define DARTSDBINPUTSTOJSON_H
#include "DbSLAs/idbjsonbuilder.h"
class QJsonObject;
template<typename T>
class IModel;
class QUuid;
class DartsDbInputsToJson : public IDbJsonBuilder<IModel<QUuid>>
{
public:
    virtual QJsonObject toJsonObject(const Json &json, const Models &models, Converter *cvtr) override;
};

#endif // DARTSDBINPUTSTOJSON_H
