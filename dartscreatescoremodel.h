#ifndef DARTSCREATESCOREMODEL_H
#define DARTSCREATESCOREMODEL_H

#include "idartscreateinput.h"
#include <qjsondocument.h>
#include <QJsonObject>
#include "dartsscoreinput.h"

class DartsCreateScoreModel : public IDartsCreateInput
{
public:
    virtual const IPlayerInput *create(const QByteArray &json) const override
    {
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            allHints = HiddenHint | DisplayHint
        };
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        auto model = DartsModelsContext::DartsScoreInput::createInstance();
        model->setScore(jsonObject.value("score").toInt());
        model->setRoundIndex(jsonObject.value("roundIndex").toInt());
        model->setSetIndex(jsonObject.value("setIndex").toInt());
        model->setPlayerId(QUuid::fromString(jsonObject.value("playerId").toString()));
        model->setPlayerName(jsonObject.value("playerName").toString());
        model->setTournamentId(QUuid::fromString(jsonObject.value("tournamentId").toString()));
        model->setHint(DisplayHint);
        model->setId(QUuid::createUuid());
        return model;
    }
};

#endif // DARTSCRETESCOREMODEL_H
