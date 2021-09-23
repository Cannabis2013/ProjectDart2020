#ifndef CREATEJSONFROMDCPLAYER_H
#define CREATEJSONFROMDCPLAYER_H

#include "DartsController/DCPlayerSLAs/icreatejsonfromdcplayer.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class CreateJsonFromDCPlayer : public ICreateJsonFromDCPlayer
{
public:
    virtual QByteArray createJson(const DCContext::IDCPlayer *playerModel) const override
    {
        auto obj = toObject(playerModel);
        return toByteArray(obj);
    }
private:
    QJsonObject toObject(const DCContext::IDCPlayer *playerModel) const
    {
        QJsonObject obj;
        obj["playerId"] = playerModel->playerId().toString(QUuid::WithoutBraces);
        obj["playerName"] = playerModel->playerName();
        return obj;
    }
    QByteArray toByteArray(const QJsonObject &obj) const
    {
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
};
#endif // CREATEJSONFROMDCPLAYER_H
