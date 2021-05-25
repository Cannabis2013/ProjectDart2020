#ifndef ASSEMBLEMULTIATTEMPTSCOREBYJSON_H
#define ASSEMBLEMULTIATTEMPTSCOREBYJSON_H

#include "iunaryservice.h"
#include "dartsscoreinput.h"
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include "qjsonobject.h"

namespace DartsModelsContext {
    class AssembleMultiAttemptScoresByJson : public IUnaryService<
            const QJsonObject&,
            QVector<const IDartsScoreInput*>>
    {
    public:
        QVector<const IDartsScoreInput *> service(const QJsonObject &jsonObject) override
        {
            QJsonArray arr = jsonObject.value("DartsMultiAttemptScores").toArray();
            QVector<const IDartsScoreInput*> list;
            for (const auto& jsonValue : arr) {
                auto jsonObject = jsonValue.toObject();
                auto model = assembleModelFromJsonObject(jsonObject);
                list << model;
            }
            return list;
        }
    private:
        const IDartsScoreInput* assembleModelFromJsonObject(const QJsonObject& jsonObject)
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
