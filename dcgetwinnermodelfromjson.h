#ifndef DCGETWINNERMODELFROMJSON_H
#define DCGETWINNERMODELFROMJSON_H

#include "idcgetwinnermodelfromjson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <dcplayer.h>
class DCGetWInnerModelsFromJson : public IDCGetWinnerModelFromJson
{
public:
    virtual const DCContext::IDCPlayer *toWinnerModel(const QByteArray &json,
                                                      const IJsonKeysPlayer *jsonKeys,
                                                      const IDCPlayerModelBuilder *playerBuilder) const override
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
    const DCContext::IDCPlayer *toModel(const QJsonObject &obj,
                                        const IJsonKeysPlayer *jsonKeys,
                                        const IDCPlayerModelBuilder *playerBuilder) const
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
