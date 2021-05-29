#ifndef DARTSSCOREBUILDERSERVICE_H
#define DARTSSCOREBUILDERSERVICE_H

#include "idartsmodelsbuilderservice.h"
#include "iplayerscoreservice.h"
#include <dartscontrollerscore.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsScoreMultiAttemptContext {
    class DartsScoreModelsBuilderService : public
            IDartsModelsBuilderService<IDartsControllerScore<QUuid,QString,QByteArray>,QByteArray,
                                       IPlayerScoreService<IDartsControllerScore<QUuid,QString,QByteArray>>>
    {
    public:
        const ModelsInterface *buildModelByJson(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto model = DartsControllerScore::createInstance();
            model->setPlayerId(QUuid(jsonObject.value("playerId").toString()));
            model->setPlayerName(jsonObject.value("playerName").toString());
            model->setScore(jsonObject.value("score").toInt());
            model->setTournamentId(QUuid(jsonObject.value("tournamentId").toString()));
            return model;
        }
        QVector<const ModelsInterface *> buildModelsByJson(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonArray = document.array();
            QVector<const ModelsInterface*> scoreModels;
            for (const auto& jsonValue : jsonArray) {
                auto newDocument = QJsonDocument(jsonValue.toObject());
                auto newJson = newDocument.toJson();
                auto scoreModel = buildModelByJson(newJson);
                scoreModels << scoreModel;
            }
            return scoreModels;
        }
        QVector<const ModelsInterface *> buildModelsByModelsService(const ScoreModelsService *service) const override
        {
            QVector<const ModelsInterface*> scoreModels;
            auto count = service->playersCount();
            for (int i = 0; i < count; ++i) {
                auto scoreModel = DartsControllerScore::createInstance();
                scoreModel->setPlayerId(service->playerIdAtIndex(i));
                scoreModel->setPlayerName(service->playerNameByIndex(i));
                scoreModel->setScore(service->playerScoreByIndex(i));
                scoreModels << scoreModel;
            }
            return scoreModels;
        }
    };
}

#endif // DARTSSCOREBUILDERSERVICE_H
