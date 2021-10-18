#ifndef DCGETWINNERMODELFROMJSON_H
#define DCGETWINNERMODELFROMJSON_H

#include "DartsController/DCPlayerSLAs/idcgetwinnermodelfromjson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "DartsController/DCPlayerServices/dcplayer.h"
class DCGetWInnerModelsFromJson : public IDCGetWinnerModelFromJson
{
public:
    virtual DCPlayer toWinnerModel(const QByteArray &json, const IDCPlayerKeys *jsonKeys,
                                   const IDCPlayerBuilder *playerBuilder) const override
    {
        return toModel(toJsonObject(json),jsonKeys,playerBuilder);
    }
private:
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject())
            return QJsonObject();
        return document.object();
    }
    DCPlayer toModel(const QJsonObject &obj, const IDCPlayerKeys *jsonKeys,
                     const IDCPlayerBuilder *playerBuilder) const
    {
        auto playerId = toId(obj.value(jsonKeys->playerId()));
        auto playerName = toString(obj.value(jsonKeys->playerName()));
        return playerBuilder->createModel(playerId,playerName);
    }
    QUuid toId(const QJsonValue &val) const
    {
        auto stringId = val.toString();
        return QUuid::fromString(stringId);
    }
    QString toString(const QJsonValue &val) const
    {
        return val.toString();
    }
};

#endif // DCGETWINNERMODELFROMJSON_H
