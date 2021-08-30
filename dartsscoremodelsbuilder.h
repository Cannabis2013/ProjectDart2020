#ifndef DARTSSCOREMODELSBUILDER_H
#define DARTSSCOREMODELSBUILDER_H

#include "idsmodelsbuilder.h"
#include <dscmodel.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
namespace DSCContext {
    class DartsScoreModelsBuilder : public IDSModelsBuilder
    {
    public:
        DSCContext::IDSCModel *createScoreModel(const QByteArray &json) const override
        {
            return createScoreModel(createJsonObject(json));
        }
        QVector<DSCContext::IDSCModel*> createScoreModels(const QByteArray &json) const override
        {
            return createScoreModels(createJsonArray(json));
        }
        QVector<DSCContext::IDSCModel*> createScoreModels(IDCScoresService* scoresService) const override
        {
            QVector<DSCContext::IDSCModel*> scoreModels;
            for (const auto &model : scoresService->tuples())
                scoreModels << createScoreModel(model);
            return scoreModels;
        }
        DSCContext::IDSCModel *createScoreModel(const int &score) const override
        {
            auto scoreModel = DSCModel::createInstance();
            scoreModel->setScore(score);
            return scoreModel;
        }
    private:
        DSCContext::IDSCModel *createScoreModel(const DCContext::DCPTuple &model) const
        {
            auto scoreModel = DSCModel::createInstance();
            scoreModel->setPlayerId(model.id);
            scoreModel->setPlayerName(model.name);
            scoreModel->setTotalScore(model.totalScore);
            return scoreModel;
        }
        QJsonArray createJsonArray(const QByteArray &json) const
        {
            auto document = QJsonDocument::fromJson(json);
            return document.array();
        }
        QVector<DSCContext::IDSCModel*> createScoreModels(const QJsonArray &arr) const
        {
            QVector<DSCContext::IDSCModel*> scoreModels;
            for (const auto& jsonValue : arr)
                scoreModels << createScoreModel(jsonValue.toObject());
            return scoreModels;
        }
        QJsonObject createJsonObject(const QByteArray &json) const
        {
            auto document = QJsonDocument::fromJson(json);
            return document.object();
        }
        DSCContext::IDSCModel *createScoreModel(const QJsonObject &obj) const
        {
            auto scoreModel = DSCModel::createInstance();
            scoreModel->setPlayerId(QUuid(obj.value("playerId").toString()));
            scoreModel->setPlayerName(obj.value("playerName").toString());
            scoreModel->setScore(obj.value("score").toInt());
            scoreModel->setTournamentId(QUuid(obj.value("tournamentId").toString()));
            return scoreModel;
        }
    };
}
#endif // DARTSSCOREBUILDERSERVICE_H
