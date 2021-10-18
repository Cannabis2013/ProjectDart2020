#ifndef DPCINPUTBUILDER_H
#define DPCINPUTBUILDER_H

#include <qjsonarray.h>
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCInputSLAs/idcinputbuilder.h"

class DPCInputBuilder : public IDCInputBuilder
{
public:
    virtual DCInput buildInput(const QByteArray &json, const IDCPlayerService *playerContext,
                               const IDCGetScore *getScoreContext, const IDCIndexService *indexContext,
                               IDCScoresService *scoresContext) const override
    {
        auto jsonObject = toJsonObject(json);
        auto input = toModel(jsonObject);
        input.playerId = playerContext->currentPlayerId(indexContext,scoresContext);
        input.playerName = playerContext->currentPlayerName(indexContext,scoresContext);
        input.score = getScoreContext->getScore(input);
        return input;
    }
    DCInput buildInput(const QByteArray &json) const override
    {
        auto jsonObject = toJsonObject(json);
        return toModel(jsonObject);
    }
    virtual DCInput buildInput(const DCContext::DCScoreModel &scoreModel) const override
    {
        return toModel(scoreModel);
    }
    virtual QVector<DCInput> buildInputs(IDCScoresService *scoresService) const override
    {
        QVector<DCInput> models;
        for (const auto &model : scoresService->scoreModels())
            models << toModel(model);
        return models;
    }
    virtual QVector<DCInput> buildInputs(const QByteArray &json) const override
    {
        QVector<DCInput> models;
        auto arr = toJsonArray(json);
        for (const auto &jsonVal : arr)
            models << toModel(jsonVal.toObject());
        return models;
    }
private:
    DCInput toModel(const QJsonObject &obj) const
    {
        DCInput input;
        input.playerId = toId(obj.value("inputPlayerId").toString());
        input.playerName = obj.value("inputPlayerName").toString();
        input.score = obj.value("score").toInt();
        input.remainingScore = obj.value("totalScore").toInt();
        input.point = obj.value("point").toInt();
        input.modKeyCode = obj.value("modKeyCode").toInt();
        return input;
    }
    DCInput toModel(const DCContext::DCScoreModel &scoreModel) const
    {
        DCInput input;
        input.playerId = scoreModel.playerId;
        input.playerName = scoreModel.playerName;
        input.remainingScore = scoreModel.totalScore;
        return input;
    }
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject())
            throw "JSON NOT OBJECT";
        return document.object();
    }
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isArray())
            throw "JSON NOT ARRAY";
        return document.array();
    }
    QByteArray toByteArray(const QJsonValue &jsonValue) const
    {
        auto document = QJsonDocument(jsonValue.toObject());
        return document.toJson();
    }
    QUuid toId(const QString &stringId) const
    {
        return QUuid::fromString(stringId);
    }
};
#endif // DARTSCONTROLLERPOINTBUILDER_H
