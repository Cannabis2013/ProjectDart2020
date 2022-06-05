#include "dartsmetamodelbuilder.h"

#include <qjsondocument.h>
#include <qjsonobject.h>

#include <DartsModelsContext/TournamentModels/dartsmetamodel.h>

DartsMetaModel DartsMetaModelBuilder::create(const QByteArray &json) const
{
    return toModel(toJsonObject(json));
}

DartsMetaModel DartsMetaModelBuilder::create(const QUuid &tournament, const QUuid &player) const
{
    return {.playerId = player,.tournamentId = tournament};
}

QJsonObject DartsMetaModelBuilder::toJsonObject(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    if(!document.isObject())
        throw "JSON NOT OBJECT";
    return document.object();
}

DartsMetaModel DartsMetaModelBuilder::toModel(const QJsonObject &obj) const
{
    DartsMetaModel meta;
    meta.playerId = toId(obj.value("currentPlayerId"));
    meta.tournamentId = toId(obj.value("tournamentId"));
    return meta;
}

QUuid DartsMetaModelBuilder::toId(const QJsonValue &value) const
{
    return QUuid::fromString(value.toString());
}
