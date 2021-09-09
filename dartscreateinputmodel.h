#ifndef DARTSCREATEINPUTMODEL_H
#define DARTSCREATEINPUTMODEL_H

#include "idartscreateinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "dartsinput.h"

class DartsCreateInputModel : public IDartsCreateInput
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    virtual const IPlayerInput *create(const QByteArray &json) const override
    {
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        auto model = new ModelsContext::DartsInput;
        model->setPoint(jsonObject.value("point").toInt());
        model->setModKeyCode(jsonObject.value("modKeyCode").toInt());
        model->setScore(jsonObject.value("score").toInt());
        model->setRoundIndex(jsonObject.value("roundIndex").toInt());
        model->setSetIndex(jsonObject.value("setIndex").toInt());
        model->setAttempt(jsonObject.value("attemptIndex").toInt());
        model->setPlayerId(QUuid::fromString(jsonObject.value("playerId").toString()));
        model->setPlayerName(jsonObject.value("playerName").toString());
        model->setTournamentId(QUuid::fromString(jsonObject.value("tournamentId").toString()));
        model->setHint(DisplayHint);
        model->setId(QUuid::createUuid());
        return model;
    }
};

#endif // DARTSCREATEDARTSPOINT_H
