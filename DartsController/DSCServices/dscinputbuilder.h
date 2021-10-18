#ifndef DSCINPUTBUILDER_H
#define DSCINPUTBUILDER_H

#include "DartsController/DCInputServices/dcinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DartsController/DCInputSLAs/idcinputbuilder.h"

class DSCInputBuilder : public IDCInputBuilder
{
public:
    virtual DCInput buildInput(const QByteArray &json, const IDCPlayerService *playerContext,
                               const IDCGetScore *getScoreContext,const IDCIndexService *indexContext,
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
        return toModel(toJsonObject(json));
    }
    virtual DCInput buildInput(const DCContext::DCScoreModel &scoreModel) const override
    {
        DCInput inputModel;
        inputModel.playerId = scoreModel.playerId;
        inputModel.playerName = scoreModel.playerName;
        inputModel.remainingScore = scoreModel.totalScore;
        return inputModel;
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
    DCInput toModel(const DCContext::DCScoreModel &model) const
    {
        DCInput scoreModel;
        scoreModel.playerId = model.playerId;
        scoreModel.playerName = model.playerName;
        scoreModel.remainingScore = model.totalScore;
        return scoreModel;
    }
    DCInput toModel(const QJsonObject &obj) const
    {
        DCInput input;
        input.playerId = toId(obj.value("inputPlayerId").toString());
        input.playerName = obj.value("inputPlayerName").toString();
        input.score = obj.value("score").toInt();
        input.remainingScore = obj.value("totalScore").toInt();
        return input ;
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
    QUuid toId(const QString &stringId) const
    {
        return QUuid::fromString(stringId);
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
