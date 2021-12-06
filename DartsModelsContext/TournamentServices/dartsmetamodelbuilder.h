#ifndef DARTSMETAMODELBUILDER_H
#define DARTSMETAMODELBUILDER_H

#include <qjsondocument.h>
#include <qjsonobject.h>

#include "DartsModelsContext/TournamentsSLAs/idartscreatemeta.h"

class DartsMetaModelBuilder : public IDartsCreateMeta
{
public:
    virtual DartsMetaModel create(const QByteArray &json) const override
    {
        return toModel(toJsonObject(json));
    }
    virtual DartsMetaModel create(const QUuid &tournament, const QUuid &player) const override
    {
        return {.playerId = player,.tournamentId = tournament};
    }
private:
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject())
            throw "JSON NOT OBJECT";
        return document.object();
    }
    DartsMetaModel toModel(const QJsonObject &obj) const
    {
        DartsMetaModel meta;
        meta.playerId = toId(obj.value("currentPlayerId"));
        meta.tournamentId = toId(obj.value("tournamentId"));
        return meta;
    }
    QUuid toId(const QJsonValue &value) const
    {
        return QUuid::fromString(value.toString());
    }
};
#endif // DARTSMETAMODELBUILDER_H
