#include "jsontodartsinputs.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qvector.h>
#include "DbSLAs/imodelconverter.h"
QVector<JsonToDartsInputs::BaseModel *> JsonToDartsInputs::convert(const ByteArray &json, Converter *cvtr) const
{
    QJsonObject obj = fromByteArray(json);
    auto arr = obj["DartsInputModels"].toArray();
    return toModels(arr,cvtr);
}

QJsonObject JsonToDartsInputs::fromByteArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    return document.object();;
}

const JsonToDartsInputs::Models JsonToDartsInputs::toModels(const QJsonArray &arr, Converter *cvtr) const
{
    QVector<IModel<QUuid>*> list;
    if(arr.isEmpty()) return Models();
    for (const auto& jsonValue : qAsConst(arr))
        list << cvtr->create(jsonValue.toObject());
    return list;
}
