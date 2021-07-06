#ifndef CREATEDARTSSCOREMODELSFROMJSON_H
#define CREATEDARTSSCOREMODELSFROMJSON_H

#include "icreateinputmodelsfromjson.h"
#include "dartsscoreinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "qjsonobject.h"

namespace DartsDbContext {
    class CreateDartsScoreModelsFromjson : public ICreateInputModelsFromJson
    {
    public:
        virtual QVector<const IPlayerInput *> create(const QByteArray &json) const override
        {
            auto jsonObject = createJsonobject(json);
            QJsonArray arr = jsonObject.value("DartsScores").toArray();
            QVector<const IPlayerInput*> list;
            for (const auto& jsonValue : arr) {
                auto jsonObject = jsonValue.toObject();
                auto model = createModelFromJsonObject(jsonObject);
                list << model;
            }
            return list;
        }
    private:
        QJsonObject createJsonobject(const QByteArray &json) const
        {
            auto document = QJsonDocument::fromJson(json);
            auto obj = document.object();
            return obj;
        }
        const DartsModelsContext::IDartsScoreInput* createModelFromJsonObject(const QJsonObject& jsonObject) const
        {
            auto stringID = jsonObject["id"].toString();
            auto id = QUuid::fromString(stringID);
            auto tournament = jsonObject["tournament"].toString();
            auto tournamentId = QUuid::fromString(tournament);
            auto playerStringID = jsonObject["playerId"].toString();
            auto playerId = QUuid::fromString(playerStringID);
            auto roundIndex = jsonObject["roundIndex"].toInt();
            auto setIndex = jsonObject["setIndex"].toInt();
            auto score = jsonObject.value("score").toInt();
            auto scoreHint = jsonObject["hint"].toInt();
            auto pointModel = DartsModelsContext::DartsScoreInput::createInstance()
                    ->setId(id)
                    ->setTournamentId(tournamentId)
                    ->setPlayerId(playerId)
                    ->setRoundIndex(roundIndex)
                    ->setSetIndex(setIndex)
                    ->setScore(score)
                    ->setHint(scoreHint);
            return pointModel;
        }
    };
}


#endif // ASSEMBLEMULTIATTEMPTSCOREBYJSON_H
