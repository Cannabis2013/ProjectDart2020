#ifndef DPCINPUTBUILDER_H
#define DPCINPUTBUILDER_H
#include <qjsonarray.h>
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCInputSLAs/idcinputbuilder.h"
class DPCInputBuilder : public IDCInputBuilder
{
public:
    virtual DCInput create(const QByteArray &json, const IDCPlayerController *playerController,
                               const IDCCalcScore *calcScoreContext,const DCIndex &index, IDCScoreModels *scoreModels) const override
    {
        auto jsonObject = toJsonObject(json);
        auto input = toModel(jsonObject);
        input.playerId = scoreModels->scores().at(index.setIndex).playerId;
        input.playerName = scoreModels->scores().at(index.setIndex).playerName;
        input.score = calcScoreContext->calculate(input);
        input.remainingScore = scoreModels->score(input.playerId).remainingScore;
        input.inGame = playerController->status(input.playerId);
        return input;
    }
    DCInput create(const QByteArray &json, const int &initialScore) const override
    {
        auto jsonObject = toJsonObject(json);
        return toModel(jsonObject,initialScore);
    }
    virtual DCInput create(const DCScoreModel &scoreModel) const override
    {
        return toModel(scoreModel);
    }
    virtual QVector<DCInput> buildInputs(IDCScoreModels *scoresService) const override
    {
        QVector<DCInput> models;
        for (const auto &model : scoresService->scores())
            models << toModel(model);
        return models;
    }
    virtual QVector<DCInput> buildInputs(const QJsonArray &arr) const override
    {
        QVector<DCInput> models;
        for (const auto &jsonVal : arr)
            models << toModel(jsonVal.toObject());
        return models;
    }
private:
    DCInput toModel(const QJsonObject &obj, const int &initialScore = -1) const
    {
        DCInput input;
        input.playerId = toId(obj.value("inputPlayerId").toString(""));
        input.playerName = obj.value("inputPlayerName").toString("");
        input.score = obj.value("score").toInt(0);
        input.remainingScore = obj.value("remainingScore").toInt(initialScore);
        input.point = obj.value("point").toInt(0);
        input.modKeyCode = obj.value("modKeyCode").toInt(0);
        input.middle = obj.value("middleValue").toDouble(0);
        input.min = obj.value("minimumValue").toInt(0);
        input.max = obj.value("maximumValue").toInt(0);
        input.inGame = obj.value("inGame").toBool(false);
        return input;
    }
    DCInput toModel(const DCScoreModel &scoreModel) const
    {
        DCInput input;
        input.playerId = scoreModel.playerId;
        input.playerName = scoreModel.playerName;
        input.remainingScore = scoreModel.remainingScore;
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
