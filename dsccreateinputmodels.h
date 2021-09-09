#ifndef DSCCREATEINPUTMODELS_H
#define DSCCREATEINPUTMODELS_H

#include "dcmodel.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <idcmodelcreator.h>

class DSCCreateInputModels : public IDCModelCreator
{
public:
    DCContext::IDCModel *createModel(const QByteArray &json, const IJsonValuesExtractor *extractor) const override
    {
        return toModel(toJsonObject(json),extractor);
    }
    QVector<DCContext::IDCModel*> createModels(IDCScoresService *scoresService) const override
    {
        QVector<DCContext::IDCModel*> scoreModels;
        for (const auto &model : scoresService->scoreModels())
            scoreModels << toModel(model);
        return scoreModels;
    }
    virtual QVector<DCContext::IDCModel *> createModels(const QByteArray &json, const IJsonValuesExtractor *extractor) const override
    {
        auto arr = toJsonArray(json);
        return toModels(arr,extractor);
    }
private:
    DCContext::IDCModel *toModel(const DCContext::DCScoreModel &model) const
    {
        auto scoreModel = DCContext::DCModel::createInstance();
        scoreModel->setPlayerId(model.id);
        scoreModel->setPlayerName(model.name);
        scoreModel->setTotalScore(model.totalScore);
        return scoreModel;
    }
    DCContext::IDCModel *toModel(const QJsonObject &obj, const IJsonValuesExtractor *extractor) const
    {
        auto scoreModel = DCContext::DCModel::createInstance();
        scoreModel->setPlayerId(extractor->toId(obj,"playerId"));
        scoreModel->setPlayerName(extractor->toString(obj,"playerName"));
        scoreModel->setScore(extractor->toInt(obj,"score"));
        scoreModel->setTournamentId(extractor->toId(obj,"tournamentId"));
        return scoreModel;
    }
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.array();
    }
    QVector<DCContext::IDCModel*> toModels(const QJsonArray &arr, const IJsonValuesExtractor *extractor) const
    {
        QVector<DCContext::IDCModel*> scoreModels;
        for (const auto& jsonValue : arr)
            scoreModels << toModel(jsonValue.toObject(),extractor);
        return scoreModels;
    }
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.object();
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
