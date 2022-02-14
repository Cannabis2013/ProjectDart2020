#include "dcmetabuilder.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qvector.h>
#include "Meta/idcmetaconverter.h"
#include "Meta/idcmetamanager.h"
#include "Index/idcindexcontroller.h"
#include "Players/idcplayermanager.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "Models/dcmeta.h"

DCMeta DCMetaBuilder::create(MetaContext *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const
{
    auto meta = metaCtx->meta();
    auto playerIndex = idxCtrl->index().playerIndex;
    meta.playerName = plaCtx->players().at(playerIndex).name;
    return meta;
}

DCMeta DCMetaBuilder::winnerMeta(MetaContext *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const
{
    auto meta = metaCtx->meta();
    auto setIndex = idxCtrl->index().playerIndex;
    meta.winnerName = plaCtx->players().at(setIndex).name;
    meta.status = metaCtx->WinnerDeclared;
    return meta;
}
