#include "dcservices.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"
#include "SLAs/absdartsctx.h"
#include "DCIndexSLAs/idcindexconverter.h"
#include "PlayerStatsSLAs/idcstatistics.h"

void DCServices::hideInput()
{
    auto idx = indexService()->undo();
    auto meta = createMeta()->create(metaService(),indexService(),plaCtx());
    mdsCtx()->hideInput(meta.tournamentId,meta.playerName,idxConverter()->convert(idx));
}

void DCServices::revealInput()
{
    auto meta = createMeta()->create(metaService(),indexService(),plaCtx());
    auto idxBa = idxConverter()->convert(indexService()->index());
    mdsCtx()->revealInput(meta.tournamentId,meta.playerName,idxBa);
}

void DCServices::updateServices(const DCInput &ipt)
{
    statisticsService()->update(ipt);
    plaCtx()->updateScore(ipt);
}

DCTurnValues DCServices::createCurrentTurnValues() const
{
    auto idx = indexService()->index();
    auto player = plaCtx()->player(idx.playerIndex);
    auto finish = finishBuilder()->suggestTargetRow(player.remScore,idx.attemptIndex);
    return turnValuesBuilder()->create(idx,player,finish);
}
