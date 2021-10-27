#include "dcjsonbuilder.h"
QByteArray DCJsonBuilder::json(const DCMetaInfo &metaInfo) const
{
    QJsonObject obj;
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const QVector<DCScoreModel> &scoreModels, const QVector<DCPlayerStat> &playerStats) const
{
    auto arr = QJsonArray();
    for (auto i = 0;i < scoreModels.count();i++)
    {
        QJsonObject obj;
        auto scoreModel = scoreModels.at(i);
        auto playerStat = playerStats.at(i);
        scoreModelJsonBuilder()->setJsonValues(obj,scoreModel);
        playerStatsJsonBuilder()->setJsonValues(obj,playerStat);
        arr << obj;
    }
    return QJsonDocument(arr).toJson();
}
QByteArray DCJsonBuilder::json(const DCInput &input, const DCTurnValues &turnValues, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    inputJsonBuilder()->setJsonValues(obj,input);
    turnValuesJsonBuilder()->setJsonValues(obj,turnValues);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCTurnValues &turnValues, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    turnValuesJsonBuilder()->setJsonValues(obj,turnValues);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCInput &input, const DCTurnValues &turnValues, const DCIndex &indexes, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    turnValuesJsonBuilder()->setJsonValues(obj,turnValues);
    inputJsonBuilder()->setJsonValues(obj,input);
    inputIndexesBuilder()->setJsonValues(obj,indexes);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCInput &input, const DCIndex &indexes, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    inputIndexesBuilder()->setJsonValues(obj,indexes);
    inputJsonBuilder()->setJsonValues(obj,input);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCIndex &index, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    inputIndexesBuilder()->setJsonValues(obj,index);
    return QJsonDocument(obj).toJson();
}

QByteArray DCJsonBuilder::json(const DCIndex &regIndex, const DCIndex &inputIndex, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    inputIndexesBuilder()->setJsonValues(obj,inputIndex);
    reqIndexJsonBuilder()->setJsonValues(obj,regIndex);
    return QJsonDocument(obj).toJson();
}

QByteArray DCJsonBuilder::json(const DCInput &input, const DCMetaInfo &metaInfo) const
{
    QJsonObject obj;
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    inputJsonBuilder()->setJsonValues(obj,input);
    return QJsonDocument(obj).toJson();
}
