#ifndef ASSEMBLEDARTSINPUTPOINTFROMJSON_H
#define ASSEMBLEDARTSINPUTPOINTFROMJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "dartspointinput.h"
#include <quuid.h>

class AssembleDartsPointModelFromJson :
        public IUnaryService<const QByteArray&,const IDartsPointInput*>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = 0x3
    };
    const IDartsPointInput* service(const QByteArray& json) override
    {
        auto jsonObject = QJsonDocument::fromJson(json).object();
        auto tournamentStringId = jsonObject.value("tournamentId").toString();
        auto tournamentId = QUuid::fromString(tournamentStringId);
        auto currentPlayerStringId = jsonObject.value("playerId").toString();
        auto playerId = QUuid::fromString(currentPlayerStringId);
        auto point = jsonObject.value("point").toInt();
        auto score = jsonObject.value("score").toInt();
        auto roundIndex = jsonObject.value("roundIndex").toInt();
        auto modKeyCode = jsonObject.value("modKeyCode").toInt();
        auto setIndex = jsonObject.value("setIndex").toInt();
        auto attemptIndex = jsonObject.value("attempt").toInt();
        auto model = DartsPointInput::createInstance()
                ->setId(QUuid::createUuid())
                ->setTournamentId(tournamentId)
                ->setPlayer(playerId)
                ->setPoint(point)
                ->setScore(score)
                ->setModKeyCode(modKeyCode)
                ->setRoundIndex(roundIndex)
                ->setSetIndex(setIndex)
                ->setAttempt(attemptIndex)
                ->setDisplayHint(DisplayHint);
        return model;
    }
};

#endif // ASSEMBLEDARTSINPUTPOINTFROMJSON_H
