#ifndef DARTSMETAMODELBUILDER_H
#define DARTSMETAMODELBUILDER_H

#include <qjsondocument.h>
#include <qjsonobject.h>

#include "DartsModelsContext/TournamentsSLAs/idartsmetamodelbuilder.h"

class DartsMetaModelBuilder : public IDartsMetaModelBuilder
{
public:
    virtual DartsMetaModel buildMetaModel(const QByteArray &json) const override
    {
        return toModel(toJsonObject(json));
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
        meta.playerName = obj.value("currentPlayerName").toString();
        meta.tournamentId = toId(obj.value("tournamentId"));
        return meta;
    }
    QUuid toId(const QJsonValue &value) const
    {
        return QUuid::fromString(value.toString());
    }
};

#endif // DARTSMETAMODELBUILDER_H
