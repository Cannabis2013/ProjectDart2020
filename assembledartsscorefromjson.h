#ifndef ASSEMBLEDARTSSCOREFROMJSON_H
#define ASSEMBLEDARTSSCOREFROMJSON_H

#include "iunary.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QJsonArray>
#include "dartsscoreinput.h"

class AssembleDartsScoreFromJson : public
        IUnary<const QByteArray&,const IDartsScoreInput<QUuid>*>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = 0x3
    };
    const IDartsScoreInput<QUuid>* service(const QByteArray& json) override
    {
        auto jsonObject = QJsonDocument::fromJson(json).object();
        auto tournamentStringId = jsonObject.value("tournamentId").toString();
        auto tournamentId = QUuid::fromString(tournamentStringId);
        auto currentPlayerStringId = jsonObject.value("playerId").toString();
        auto playerId = QUuid::fromString(currentPlayerStringId);
        auto roundIndex = jsonObject.value("roundIndex").toInt();
        auto setIndex = jsonObject.value("setIndex").toInt();
        auto attempt = jsonObject.value("attempt").toInt();
        auto point = jsonObject.value("point").toInt();
        auto score = jsonObject.value("scoreValue").toInt();
        auto accumulatedScore = jsonObject.value("accumulatedScoreValue").toInt();
        auto modKeyCode = jsonObject.value("modKeyCode").toInt();
        auto model = DartsScoreInput::createInstance()
                ->setId(QUuid::createUuid())
                ->setTournament(tournamentId)
                ->setPlayer(playerId)
                ->setRoundIndex(roundIndex)
                ->setSetIndex(setIndex)
                ->setAttempt(attempt)
                ->setPointValue(point)
                ->setScoreValue(score)
                ->setAccumulatedScore(accumulatedScore)
                ->setModKeyCode(modKeyCode)
                ->setDisplayHint(DisplayHint);
        return model;
    }
};

#endif // ASSEMBLEDARTSSCOREFROMJSON_H
