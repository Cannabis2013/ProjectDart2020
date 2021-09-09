#ifndef DPCCREATEINPUTMODELS_H
#define DPCCREATEINPUTMODELS_H

#include <qjsonarray.h>
#include "dcmodel.h"
#include "idcmodelcreator.h"


class DPCCreateInputModels : public IDCModelCreator
{
public:
    DCContext::IDCModel *createModel(const QByteArray &json, const IJsonValuesExtractor *extractor) const override
    {
        auto jsonObject = toJsonObject(json);
        return toModel(jsonObject,extractor);
    }
    QVector<DCContext::IDCModel*> createModels(const QByteArray &json, const IJsonValuesExtractor *extractor) const override
    {
        QVector<DCContext::IDCModel*> dartsPointModels;
        for (const auto &jsonVal : toJsonArray(json))
            dartsPointModels << createModel(toByteArray(jsonVal),extractor);
        return dartsPointModels;
    }
    virtual QVector<DCContext::IDCModel *> createModels(IDCScoresService *scoresService) const override
    {
        QVector<DCContext::IDCModel*> models;
        for (const auto &tuple : scoresService->scoreModels())
            models << toModel(tuple);
        return models;
    }
private:
    DCContext::DCModel *toModel(const QJsonObject &jsonObject, const IJsonValuesExtractor *extractor) const
    {
        auto model = DCContext::DCModel::createInstance();
        model->setScore(extractor->toInt(jsonObject,"score"));
        model->setPoint(extractor->toInt(jsonObject,"point"));
        model->setModKeyCode(extractor->toInt(jsonObject,"modKeyCode"));
        model->setTotalScore(extractor->toInt(jsonObject,"totalScore"));
        model->setPlayerId(extractor->toId(jsonObject,"playerId"));
        model->setPlayerName(extractor->toString(jsonObject,"playerName"));
        model->setTotalScore(0);
        return model;
    }
    DCContext::DCModel *toModel(const DCContext::DCScoreModel &tuple) const
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

};
#endif // DARTSCONTROLLERPOINTBUILDER_H
