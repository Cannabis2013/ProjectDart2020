#ifndef DPCINPUTBUILDER_H
#define DPCINPUTBUILDER_H

#include <qjsonarray.h>
#include "DartsController/DCInputServices/dcinputmodel.h"
#include "DartsController/DCInputSLAs/idcinputbuilder.h"


class DPCInputBuilder : public IDCInputBuilder
{
public:
    DCContext::IDCInputModel *createModel(const QByteArray &json) const override
    {
        auto jsonObject = toJsonObject(json);
        return toModel(jsonObject);
    }
    virtual DCContext::IDCInputModel *createModel(const DCContext::DCScoreModel &scoreModel) const override
    {
        return toModel(scoreModel);
    }
    virtual QVector<DCContext::IDCInputModel *> createModels(IDCScoresService *scoresService) const override
    {
        QVector<DCContext::IDCInputModel *> models;
        for (const auto &model : scoresService->scoreModels())
            models << toModel(model);
        return models;
    }
    virtual QVector<DCContext::IDCInputModel *> createModels(const QByteArray &json) const override
    {
        QVector<DCContext::IDCInputModel *> models;
        auto arr = toJsonArray(json);
        for (const auto &jsonVal : arr)
            models << toModel(jsonVal.toObject());
        return models;
    }
private:
    DCContext::DCInputModel *toModel(const QJsonObject &obj) const
    {
        auto input = DCContext::DCInputModel::createInstance();
        input->setPlayerId(toId(obj.value("inputPlayerId").toString()));
        input->setPlayerName(obj.value("inputPlayerName").toString());
        input->setScore(obj.value("score").toInt());
        input->setTotalScore(obj.value("totalScore").toInt());
        input->setPoint(obj.value("point").toInt());
        input->setModKeyCode(obj.value("modKeyCode").toInt());
        return input;
    }
    DCContext::DCInputModel *toModel(const DCContext::DCScoreModel &scoreModel) const
    {
        auto inputModel = DCContext::DCInputModel::createInstance();
        inputModel->setPlayerId(scoreModel.playerId);
        inputModel->setPlayerName(scoreModel.playerName);
        inputModel->setTotalScore(scoreModel.totalScore);
        return inputModel;
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
