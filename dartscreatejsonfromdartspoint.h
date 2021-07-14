#ifndef DARTSCREATEJSONFROMDARTSPOINT_H
#define DARTSCREATEJSONFROMDARTSPOINT_H

#include "idartscreatejsonfrommodel.h"
#include "idartspointinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class DartsCreateJsonFromPointModel : public IDartsCreateJsonFromModel<IPlayerInput>
{
public:
    virtual QByteArray createJson(const IPlayerInput *inputModel) const override
    {
        auto model = dynamic_cast<const DartsModelsContext::IDartsPointInput*>(inputModel);
        QJsonObject jsonObject;
        jsonObject["point"] = model->point();
        jsonObject["score"] = model->score();
        jsonObject["modKeyCode"] = model->modKeyCode();
        jsonObject["roundIndex"] = model->roundIndex();
        jsonObject["setIndex"] = model->setIndex();
        jsonObject["attempt"] = model->attempt();
        jsonObject["hint"] = model->hint();
        jsonObject["id"] = model->id().toString(QUuid::WithoutBraces);
        jsonObject["playerId"] = model->playerId().toString(QUuid::WithoutBraces);
        jsonObject["playerName"] = model->playerName();
        jsonObject["tournamentId"] = model->tournamentId().toString(QUuid::WithoutBraces);
        auto document = QJsonDocument(jsonObject);
        auto json = document.toJson();
        return json;
    }
};

#endif // DARTSCREATEJSONFROMDARTSPOINT_H
