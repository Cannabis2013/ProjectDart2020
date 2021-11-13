#include "dcjsonbuilder.h"
QByteArray DCJsonBuilder::create(const DCMeta &metaInfo) const
{
    QJsonObject obj;
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::create(const QVector<DCScoreModel> &scoreModels, const QVector<DCPlayerStat> &playerStats) const
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
QByteArray DCJsonBuilder::create(AbstractDartsInput *input, const DCTurnValues &turnValues, const DCMeta &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    inputJsonBuilder()->setJsonValues(obj,input);
    turnValuesJsonBuilder()->setJsonValues(obj,turnValues);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::create(const DCTurnValues &turnValues, const DCMeta &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    turnValuesJsonBuilder()->setJsonValues(obj,turnValues);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::create(AbstractDartsInput *input, const DCTurnValues &turnValues, IDartsIndex *index, const DCMeta &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    turnValuesJsonBuilder()->setJsonValues(obj,turnValues);
    inputJsonBuilder()->setJsonValues(obj,input);
    inputIndexesBuilder()->setJsonValues(obj,index);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::create(AbstractDartsInput *input, IDartsIndex *index, const DCMeta &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    inputIndexesBuilder()->setJsonValues(obj,index);
    inputJsonBuilder()->setJsonValues(obj,input);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::create(IDartsIndex *index, const DCMeta &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    inputIndexesBuilder()->setJsonValues(obj,index);
    return QJsonDocument(obj).toJson();
}

QByteArray DCJsonBuilder::create(IDartsIndex *regIndex, IDartsIndex *inputIndex, const DCMeta &metaInfo) const
{
    auto obj = QJsonObject();
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    inputIndexesBuilder()->setJsonValues(obj,inputIndex);
    reqIndexJsonBuilder()->setJsonValues(obj,regIndex);
    return QJsonDocument(obj).toJson();
}

QByteArray DCJsonBuilder::create(AbstractDartsInput *input, const DCMeta &metaInfo) const
{
    QJsonObject obj;
    metaJsonBuilder()->setJsonValues(obj,metaInfo);
    inputJsonBuilder()->setJsonValues(obj,input);
    return QJsonDocument(obj).toJson();
}
