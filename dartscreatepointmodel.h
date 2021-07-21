#ifndef DARTSCREATEPOINTMODEL_H
#define DARTSCREATEPOINTMODEL_H

#include "idartscreateinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "dartspointinput.h"

class DartsCreatePointModel : public IDartsCreateInput
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
        auto model = ModelsContext::DartsPointInput::createInstance();
        model->setPoint(jsonObject.value("point").toInt());
        model->setModKeyCode(jsonObject.value("modKeyCode").toInt());
        model->setScore(jsonObject.value("score").toInt());
        model->setRoundIndex(jsonObject.value("roundIndex").toInt());
        model->setSetIndex(jsonObject.value("setIndex").toInt());
        model->setAttempt(jsonObject.value("attempt").toInt());
        model->setPlayerId(QUuid::fromString(jsonObject.value("playerId").toString()));
        model->setPlayerName(jsonObject.value("playerName").toString());
        model->setTournamentId(QUuid::fromString(jsonObject.value("tournamentId").toString()));
        model->setHint(DisplayHint);
        model->setId(QUuid::createUuid());
        return model;
    }
};

#endif // DARTSCREATEDARTSPOINT_H
