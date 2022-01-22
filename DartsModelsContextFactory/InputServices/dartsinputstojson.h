#ifndef DARTSINPUTSTOJSON_H
#define DARTSINPUTSTOJSON_H
#include "InputModelsSLAs/idartsinputstojson.h"
class QUuid;
template<typename T>
class IModel;
class QJsonArray;
class QJsonObject;
class QByteArray;
class IDartsInput;
class DartsInputsToJson : public IDartsInputsToJson<IModel<QUuid>>
{
public:
    virtual ByteArray toJson(const Models &models, Converter *cvtr) const override;
private:
    QByteArray toByteArray(const QJsonArray &arr) const;
};
#endif // DARTSINPUTSTOJSON_H
