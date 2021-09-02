#ifndef DPCCREATEINPUTMODELS_H
#define DPCCREATEINPUTMODELS_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "dcmodel.h"
#include "idcmodelcreator.h"

class DPCCreateInputModels : public IDCModelCreator
{
public:
    DCContext::IDCModel *createModel(const QByteArray &json) const override
    {
        auto jsonObject = toJsonObject(json);
        return toModel(jsonObject);
    }
    QVector<DCContext::IDCModel*> createModels(const QByteArray &json) const override
    {
        QVector<DCContext::IDCModel*> dartsPointModels;
        for (const auto &jsonVal : toJsonArray(json))
            dartsPointModels << createModel(toByteArray(jsonVal));
        return dartsPointModels;
    }
    DCContext::IDCModel *createModel(const int &point, const int &score, const int &modKeyCode) const override
    {
        auto model = DCContext::DCModel::createInstance();
        model->setPoint(point);
        model->setScore(score);
        model->setModKeyCode(modKeyCode);
        return model;
    }
    virtual QVector<DCContext::IDCModel *> createModels(IDCScoresService *scoresService) const override
    {
        QVector<DCContext::IDCModel*> models;
        for (const auto &tuple : scoresService->tuples())
            models << toModel(tuple);
        return models;
    }
private:
    DCContext::DCModel *toModel(const QJsonObject &jsonObject) const
    {
        auto model = DCContext::DCModel::createInstance();
        model->setScore(jsonObject.value("score").toInt());
        model->setPoint(jsonObject.value("point").toInt());
        model->setTotalScore(jsonObject.value("totalScore").toInt());
        model->setModKeyCode( jsonObject.value("modKeyCode").toInt());
        model->setPlayerId(toId(jsonObject,"playerId"));
        model->setPlayerName(jsonObject.value("playerName").toString());
        model->setTotalScore(0);
        return model;
    }
    DCContext::DCModel *toModel(const DCContext::DCPTuple &tuple) const
    {
        auto inputModel = DCContext::DCModel::createInstance();
        inputModel->setPlayerId(tuple.id);
        inputModel->setPlayerName(tuple.name);
        inputModel->setTotalScore(tuple.totalScore);
        return inputModel;
    }
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.object();
    }
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.array();
    }
    QByteArray toByteArray(const QJsonValue &jsonValue) const
    {
        auto document = QJsonDocument(jsonValue.toObject());
        return document.toJson();
    }
    QUuid toId(const QJsonObject &obj, const QString &key) const
    {
        auto stringId = obj[key].toString();
        return QUuid::fromString(stringId);
    }
};
#endif // DARTSCONTROLLERPOINTBUILDER_H
