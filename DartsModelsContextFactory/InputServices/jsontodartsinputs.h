#ifndef JSONTODARTSINPUTS_H
#define JSONTODARTSINPUTS_H
#include "DbSLAs/iconvertfromdata.h"
class QJsonArray;
class QJsonObject;
class QUuid;
class QByteArray;
template<typename T>
class IModel;
class JsonToDartsInputs : public IConvertFromData<IModel<QUuid>>
{
public:
    virtual QVector<BaseModel *> convert(const ByteArray &json, Converter *cvtr) const override;
private:
    QJsonObject fromByteArray(const QByteArray &json) const;
    const Models toModels(const QJsonArray &arr, Converter *cvtr) const;
};
#endif // JSONTODARTSINPUTS_H
