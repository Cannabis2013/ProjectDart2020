#include "jsontodartsmodels.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonarray.h>
#include <qbytearray.h>
#include <quuid.h>
#include <qvector.h>
#include "DbSLAs/imodelconverter.h"
#include "TournamentModels/dartstournament.h"
#include "ModelSLAs/imodel.h"
QVector<JsonToDartsModels::BaseModel *> JsonToDartsModels::convert(const ByteArray &json, Converter *cvtr) const
{
    QJsonObject obj = fromByteArray(json);
    auto arr = obj["DartsTournamentModels"].toArray();
    return toModels(arr,cvtr);
}

QJsonObject JsonToDartsModels::fromByteArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    return document.object();;
}

const JsonToDartsModels::Models JsonToDartsModels::toModels(const QJsonArray &arr, Converter *cvtr) const
{
    QVector<IModel<QUuid>*> list;
    if(arr.isEmpty()) return Models();
    for (const auto& jsonValue : qAsConst(arr))
        list << cvtr->create(jsonValue.toObject());
    return list;
}
