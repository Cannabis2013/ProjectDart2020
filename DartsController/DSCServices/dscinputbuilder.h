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
    virtual DCInput buildInput(const QByteArray &json, const IDCGetScore *getScoreContext,
                               const DCIndex &index, IDCScoreModels *scoresContext) const override
    {
        auto jsonObject = toJsonObject(json);
        auto input = toInput(jsonObject);
        input.playerId = scoresContext->scores().at(index.setIndex).playerId;
        input.playerName = scoresContext->scores().at(index.setIndex).playerName;
        input.score = getScoreContext->getScore(input);
        input.remainingScore = scoresContext->score(input.playerId).remainingScore;
        return input;
    }
    DCInput buildInput(const QByteArray &json, const int &initialScore) const override
    {
        return toInput(toJsonObject(json),initialScore);
    }
    virtual DCInput buildInput(const DCScoreModel &scoreModel) const override
    {
        DCInput inputModel;
        inputModel.playerId = scoreModel.playerId;
        inputModel.playerName = scoreModel.playerName;
        inputModel.remainingScore = scoreModel.remainingScore;
        return inputModel;
    }
    virtual QVector<DCInput> buildInputs(IDCScoreModels *scoresService) const override
    {
        QVector<DCInput> scoreModels;
        for (const auto &scoreModel : scoresService->scores())
            scoreModels << toInput(scoreModel);
        return scoreModels;
    }
    virtual QVector<DCInput> buildInputs(const QByteArray &json) const override
    {
        QVector<DCInput> models;
        auto arr = toJsonArray(json);
        for (const auto &jsonVal : arr)
            models << toInput(jsonVal.toObject());
        return models;
    }
private:
    DCInput toInput(const DCScoreModel &scoreModel) const
    {
        DCInput input;
        input.playerId = scoreModel.playerId;
        input.playerName = scoreModel.playerName;
        input.remainingScore = scoreModel.remainingScore;
        return input;
    }
    DCInput toInput(const QJsonObject &obj, const int &initialScore = -1) const
    {
        DCInput input;
        input.playerId = toId(obj.value("inputPlayerId").toString());
        input.playerName = obj.value("inputPlayerName").toString();
        input.score = obj.value("score").toInt();
        input.remainingScore = obj.value("totalScore").toInt();
        input.middle = obj.value("middleValue").toDouble(0);
        input.min = obj.value("currentMinimum").toInt(0);
        input.max = obj.value("currentMaximum").toInt(0);
        input.remainingScore = obj.value("remainingScore").toInt(initialScore);
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
