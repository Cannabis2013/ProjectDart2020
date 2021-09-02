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
    DCContext::IDCModel *createModel(const QByteArray &json) const override
    {
        return toScoreModel(toJsonObject(json));
    }
    DCContext::IDCModel *createModel(const int &score, const int &point, const int &modKeyCode) const override
    {
        auto scoreModel = DCContext::DCModel::createInstance();
        scoreModel->setScore(score);
        scoreModel->setPoint(point);
        scoreModel->setModKeyCode(modKeyCode);
        return scoreModel;
    }
    QVector<DCContext::IDCModel*> createModels(IDCScoresService *scoresService) const override
    {
        QVector<DCContext::IDCModel*> scoreModels;
        for (const auto &model : scoresService->tuples())
            scoreModels << toScoreModel(model);
        return scoreModels;
    }
    virtual QVector<DCContext::IDCModel *> createModels(const QByteArray &json) const override
    {
        auto arr = toJsonArray(json);
        return toScoreModels(arr);
    }
private:
    DCContext::IDCModel *toScoreModel(const DCContext::DCPTuple &model) const
    {
        auto scoreModel = DCContext::DCModel::createInstance();
        scoreModel->setPlayerId(model.id);
        scoreModel->setPlayerName(model.name);
        scoreModel->setTotalScore(model.totalScore);
        return scoreModel;
    }
    DCContext::IDCModel *toScoreModel(const QJsonObject &obj) const
    {
        auto scoreModel = DCContext::DCModel::createInstance();
        scoreModel->setPlayerId(QUuid(obj.value("playerId").toString()));
        scoreModel->setPlayerName(obj.value("playerName").toString());
        scoreModel->setScore(obj.value("score").toInt());
        scoreModel->setTournamentId(QUuid(obj.value("tournamentId").toString()));
        return scoreModel;
    }
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.array();
    }
    QVector<DCContext::IDCModel*> toScoreModels(const QJsonArray &arr) const
    {
        QVector<DCContext::IDCModel*> scoreModels;
        for (const auto& jsonValue : arr)
            scoreModels << toScoreModel(jsonValue.toObject());
        return scoreModels;
    }
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.object();
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
