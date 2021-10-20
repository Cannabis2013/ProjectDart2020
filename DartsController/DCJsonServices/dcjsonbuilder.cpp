#include "dcjsonbuilder.h"
QByteArray DCJsonBuilder::json(const DCMetaInfo &metaInfo) const
{
    QJsonObject obj;
    metaJsonBuilder()->json(obj,metaInfo);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const QVector<DCInput> &inputs) const
{
    auto arr = QJsonArray();
    for (const auto &input : inputs) {
        QJsonObject obj;
        inputJsonBuilder()->json(obj,input);
        arr << obj;
    }
    return QJsonDocument(arr).toJson();
}
QByteArray DCJsonBuilder::json(const DCInput &input, const DCTurnValues &turnValues, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->json(obj,metaInfo);
    inputJsonBuilder()->json(obj,input);
    turnValuesJsonBuilder()->json(obj,turnValues);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCTurnValues &turnValues, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->json(obj,metaInfo);
    turnValuesJsonBuilder()->json(obj,turnValues);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCInput &input, const DCTurnValues &turnValues, const DCIndexes &indexes,
                               const DCInputStat &stats, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->json(obj,metaInfo);
    turnValuesJsonBuilder()->json(obj,turnValues);
    inputJsonBuilder()->json(obj,input);
    indexesJsonBuilder()->json(obj,indexes);
    inputStatJsonBuilder()->json(obj,stats);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCInput &input, const DCIndexes &indexes, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->json(obj,metaInfo);
    indexesJsonBuilder()->json(obj,indexes);
    inputJsonBuilder()->json(obj,input);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCIndexes &indexes, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->json(obj,metaInfo);
    indexesJsonBuilder()->json(obj,indexes);
    return QJsonDocument(obj).toJson();
}
