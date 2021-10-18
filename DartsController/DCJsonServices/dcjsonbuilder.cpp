#include "dcjsonbuilder.h"
QByteArray DCJsonBuilder::json(const DCMetaInfo &metaInfo) const
{
    QJsonObject obj;
    setMetaJsonValues(obj,metaInfo);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const QVector<DCInput> &inputs) const
{
    auto arr = QJsonArray();
    for (const auto &input : inputs) {
        QJsonObject obj;
        setInputJsonValues(obj,input);
        arr << obj;
    }
    return QJsonDocument(arr).toJson();
}
QByteArray DCJsonBuilder::json(const DCInput &input, const DCTurnValues &turnValues, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    setMetaJsonValues(obj,metaInfo);
    setInputJsonValues(obj,input);
    setTurnValuesJsonValues(obj,turnValues);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCTurnValues &turnValues, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    setMetaJsonValues(obj,metaInfo);
    setTurnValuesJsonValues(obj,turnValues);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCInput &input, const DCIndexes &indexes, const int &average, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    setMetaJsonValues(obj,metaInfo);
    setInputJsonValues(obj,input);
    setIndexesJsonValues(obj,indexes);
    obj["average"] = average;
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCInput &input, const DCIndexes &indexes, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    setMetaJsonValues(obj,metaInfo);
    setIndexesJsonValues(obj,indexes);
    setInputJsonValues(obj,input);
    return QJsonDocument(obj).toJson();
}
QByteArray DCJsonBuilder::json(const DCIndexes &indexes, const DCMetaInfo &metaInfo) const
{
    auto obj = QJsonObject();
    setMetaJsonValues(obj,metaInfo);
    setIndexesJsonValues(obj,indexes);
    return QJsonDocument(obj).toJson();
}
void DCJsonBuilder::setMetaJsonValues(QJsonObject &obj, const DCMetaInfo &metaInfo) const
{
    obj["tournamentId"] = metaInfo.tournamentId.toString(QUuid::WithoutBraces);
    obj["currentPlayerId"] = metaInfo.currentPlayerId.toString(QUuid::WithoutBraces);
    obj["currentPlayerName"] = metaInfo.currentPlayerName;
    obj["winnerId"] = metaInfo.winnerId.toString(QUuid::WithoutBraces);
    obj["winnerName"] = metaInfo.winnerName;
}
void DCJsonBuilder::setTurnValuesJsonValues(QJsonObject &obj, const DCTurnValues &turnValues) const
{
    obj["currentRoundIndex"] = turnValues.roundIndex;
    obj["currentSetIndex"] = turnValues.setIndex;
    obj["currentAttemptIndex"] = turnValues.attemptIndex;
    obj["canUndo"] = turnValues.canUndo;
    obj["canRedo"] = turnValues.canRedo;
    obj["suggestedFinish"] = turnValues.targetRow;
    obj["currentPlayerName"] = turnValues.playerName;
}
void DCJsonBuilder::setInputJsonValues(QJsonObject &obj, const DCInput &input) const
{
    obj["point"] = input.point;
    obj["modKeyCode"] = input.modKeyCode;
    obj["score"] = input.score;
    obj["inputPlayerId"] = input.playerId.toString(QUuid::WithoutBraces);
    obj["inputPlayerName"] = input.playerName;
    obj["totalScore"] = input.remainingScore;
}
void DCJsonBuilder::setIndexesJsonValues(QJsonObject &obj, const DCIndexes &indexes) const
{
    obj["totalTurns"] = indexes.totalTurns;
    obj["turnIndex"] = indexes.turnIndex;
    obj["roundIndex"] = indexes.roundIndex;
    obj["setIndex"] = indexes.setIndex;
    obj["attemptIndex"] = indexes.attemptIndex;
}
