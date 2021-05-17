#ifndef ASSEMBLEDARTSSCOREFROMJSON_H
#define ASSEMBLEDARTSSCOREFROMJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QJsonArray>
#include "dartsscoreinput.h"

class AssembleDartsScoreFromJson : public
        IUnaryService<const QByteArray&,const IDartsScoreInput*>
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
        auto roundIndex = jsonObject.value("roundIndex").toInt();
        auto setIndex = jsonObject.value("setIndex").toInt();
        auto score = jsonObject.value("scoreValue").toInt();
        auto model = DartsScoreInput::createInstance()
                ->setId(QUuid::createUuid())
                ->setTournamentId(tournamentId)
                ->setPlayer(playerId)
                ->setRoundIndex(roundIndex)
                ->setSetIndex(setIndex)
                ->setScore(score)
                ->setHint(DisplayHint);
        return model;
    }
};

#endif // ASSEMBLEDARTSSCOREFROMJSON_H
