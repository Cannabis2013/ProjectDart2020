#ifndef DSCCREATEINPUTMODELS_H
#define DSCCREATEINPUTMODELS_H

#include "DartsController/DCInputServices/dcinputmodel.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DartsController/DCInputSLAs/idccreateinputmodel.h"

class DSCCreateInputModel : public IDCCreateInputModel
{
public:
    DCContext::IDCInputModel *createModel(const QByteArray &json) const override
    {
        return toModel(toJsonObject(json));
    }
    virtual DCContext::IDCInputModel *createModel(const DCContext::DCScoreModel &scoreModel) const override
    {
        auto inputModel = DCContext::DCInputModel::createInstance();
        inputModel->setPlayerId(scoreModel.playerId);
        inputModel->setPlayerName(scoreModel.playerName);
        inputModel->setTotalScore(scoreModel.totalScore);
        return inputModel;
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
    DCContext::IDCInputModel *toModel(const DCContext::DCScoreModel &model) const
    {
        auto scoreModel = DCContext::DCInputModel::createInstance();
        scoreModel->setPlayerId(model.playerId);
        scoreModel->setPlayerName(model.playerName);
        scoreModel->setTotalScore(model.totalScore);
        return scoreModel;
    }
    DCContext::IDCInputModel *toModel(const QJsonObject &obj) const
    {
        auto input = DCContext::DCInputModel::createInstance();
        input->setPlayerId(toId(obj.value("inputPlayerId").toString()));
        input->setPlayerName(obj.value("inputPlayerName").toString());
        input->setScore(obj.value("score").toInt());
        input->setTotalScore(obj.value("totalScore").toInt());
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
