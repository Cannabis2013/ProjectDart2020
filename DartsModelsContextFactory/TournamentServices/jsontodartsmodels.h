#ifndef JSONTODARTSMODELS_H
#define JSONTODARTSMODELS_H
#include "DbSLAs/iconvertfromdata.h"
class QJsonArray;
class QJsonObject;
class QUuid;
class QByteArray;
template<typename T>
class IModel;
class JsonToDartsModels : public IConvertFromData<IModel<QUuid>>
{
public:
    virtual QVector<BaseModel *> convert(const ByteArray &json, Converter *cvtr) const override;
private:
    QJsonObject fromByteArray(const QByteArray &json) const;
    const Models toModels(const QJsonArray &arr, Converter *cvtr) const;
};
#endif // JSONTODARTSMODELS_H
