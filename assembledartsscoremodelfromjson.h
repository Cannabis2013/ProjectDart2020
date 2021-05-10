#ifndef ASSEMBLEDARTSSCOREMODELFROMJSON_H
#define ASSEMBLEDARTSSCOREMODELFROMJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "dartsscoreinput.h"
#include <quuid.h>

class AssembleDartsScoreModelFromJson :
        public IUnaryService<const QByteArray&,const IDartsScoreInput*>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = 0x3
    };
    const IDartsScoreInput* service(const QByteArray& json) override
    {
        auto jsonObject = QJsonDocument::fromJson(json).object();
        auto tournamentStringId = jsonObject.value("tournamentId").toString();
        auto tournamentId = QUuid::fromString(tournamentStringId);
        auto currentPlayerStringId = jsonObject.value("playerId").toString();
        auto playerId = QUuid::fromString(currentPlayerStringId);
        auto score = jsonObject.value("score").toInt();
        auto roundIndex = jsonObject.value("roundIndex").toInt();
        auto setIndex = jsonObject.value("setIndex").toInt();
        auto model = DartsScoreInput::createInstance()
                ->setId(QUuid::createUuid())
                ->setTournamentId(tournamentId)
                ->setPlayer(playerId)
                ->setScore(score)
                ->setRoundIndex(roundIndex)
                ->setSetIndex(setIndex)
                ->setHint(DisplayHint);
        return model;
    }
};

#endif // ASSEMBLEDARTSSCOREMODELFROMJSON_H
