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
    IDCInput *createModel(const QByteArray &json) const override
    {
        return toModel(toJsonObject(json));
    }
    virtual IDCInput *createModel(const DCContext::DCScoreModel &scoreModel) const override
    {
        auto inputModel = DCInput::createInstance();
        inputModel->setPlayerId(scoreModel.playerId);
        inputModel->setPlayerName(scoreModel.playerName);
        inputModel->setTotalScore(scoreModel.totalScore);
        return inputModel;
    }
    virtual QVector<IDCInput *> createModels(IDCScoresService *scoresService) const override
    {
        QVector<IDCInput *> models;
        for (const auto &model : scoresService->scoreModels())
            models << toModel(model);
        return models;
    }
    virtual QVector<IDCInput *> createModels(const QByteArray &json) const override
    {
        QVector<IDCInput *> models;
        auto arr = toJsonArray(json);
        for (const auto &jsonVal : arr)
            models << toModel(jsonVal.toObject());
        return models;
    }
private:
    IDCInput *toModel(const DCContext::DCScoreModel &model) const
    {
        auto scoreModel = DCInput::createInstance();
        scoreModel->setPlayerId(model.playerId);
        scoreModel->setPlayerName(model.playerName);
        scoreModel->setTotalScore(model.totalScore);
        return scoreModel;
    }
    IDCInput *toModel(const QJsonObject &obj) const
    {
        auto input = DCInput::createInstance();
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
