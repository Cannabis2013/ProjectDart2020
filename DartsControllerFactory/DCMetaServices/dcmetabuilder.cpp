#include "dcmetabuilder.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qvector.h>
#include "DCMetaSLAs/IDCMetaConverter.h"
#include "DCMetaSLAs/idcmetacontext.h"
#include "DCIndexSLAs/idcindexcontroller.h"
#include "DCScoresSLAs/absdcplayersctx.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "Models/dcmeta.h"

DCMeta DCMetaBuilder::create(MetaCtx *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const
{
    auto meta = metaCtx->meta();
    auto setIndex = idxCtrl->index().playerIndex;
    meta.playerName = plaCtx->players().at(setIndex).name;
    return meta;
}

DCMeta DCMetaBuilder::create(const QByteArray &json) const
{
    DCMeta meta = toMeta(toJson(json));
    return meta;
}

DCMeta DCMetaBuilder::winnerMeta(MetaCtx *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const
{
    auto meta = metaCtx->meta();
    auto setIndex = idxCtrl->index().playerIndex;
    meta.winnerName = plaCtx->players().at(setIndex).name;
    meta.status = metaCtx->WinnerDeclared;
    return meta;
}

QJsonObject DCMetaBuilder::toJson(const ByteArray &byteArray) const
{
    return QJsonDocument::fromJson(byteArray).object();
}

DCMeta DCMetaBuilder::toMeta(const QJsonObject &json) const
{
    DCMeta meta;
    meta.entryRestricted = json.value("entryRestricted").toBool();
    meta.initRemScore = json.value("initRemScore").toInt();
    meta.playersCount = json.value("assignedPlayersCount").toInt();
    meta.tournamentId = toId(json.value("tournamentId").toString());
    meta.winnerName = json.value("winnerName").toString();
    meta.index.roundIndex = json.value("roundIndex").toInt();
    meta.index.playerIndex = json.value("playerIndex").toInt();
    meta.index.attemptIndex = json.value("attemptIndex").toInt();
    return meta;
}

QUuid DCMetaBuilder::toId(const QString &stringId) const
{
    return QUuid::fromString(stringId);
}
