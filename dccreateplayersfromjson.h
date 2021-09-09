#ifndef DCCREATEPLAYERSFROMJSON_H
#define DCCREATEPLAYERSFROMJSON_H

#include "idccreateplayersfromjson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class DCCreatePlayersFromJson : public IDCCreatePlayersFromJson
{
    // IDCCreatePlayerModelsFromJson interface
public:
    virtual QVector<const DCContext::IDCPlayer *> createModels(const QByteArray &json,
                                                               const IJsonKeysPlayer *jsonKeys,
                                                               const IDCPlayerModelBuilder *playerBuilder) const override
    {
        auto arr = toJsonArray(json);
        return toPlayerModels(arr,jsonKeys,playerBuilder);
    }
private:
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.array();
    }
    QJsonObject toJsonObject(const QJsonValue &val) const
    {
        if(!val.isObject())
            return QJsonObject();
        return val.toObject();
    }
    const QVector<const DCContext::IDCPlayer*> toPlayerModels(const QJsonArray &arr,
                                                        const IJsonKeysPlayer *jsonKeys,
                                                        const IDCPlayerModelBuilder *playerBuilder) const
    {
        QVector<const DCContext::IDCPlayer*> models;
        for (const auto &val : arr)
            models << toPlayerModel(toJsonObject(val),jsonKeys,playerBuilder);
        return models;
    }
    const DCContext::IDCPlayer *toPlayerModel(const QJsonObject &obj,
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

#endif // DCCREATEPLAYERSFROMJSON_H
