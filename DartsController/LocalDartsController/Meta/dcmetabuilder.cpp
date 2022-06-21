#include "dcmetabuilder.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qvector.h>
#include <DartsController/Contracts/Meta/idcmetamanager.h>
#include <DartsController/Contracts/Index/idcindexcontroller.h>
#include <DartsController/Contracts/Models/dcindex.h>
#include <DartsController/Contracts/Models/dcmeta.h>
#include <DartsController/Contracts/Models/dcplayer.h>
#include <DartsController/Contracts/Players/idcplayermanager.h>

DCMeta DCMetaBuilder::create(MetaContext *metaContext, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const
{
        auto meta = metaContext->meta();
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
