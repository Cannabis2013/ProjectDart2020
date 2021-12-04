#ifndef DCRESETCONTEXTS_H
#define DCRESETCONTEXTS_H
#include "DartsController/DCIndexSLAs/absdcidxctrl.h"
#include "DartsController/DCScoresSLAs/absdcplayersctx.h"
#include "DartsController/PlayerStatsSLAs/idcstatscontext.h"
class DCResetContexts
{
public:
    static void reset(AbsDCIdxCtrl *indexCtrl, AbsDCPlayersCtx *scoresContext, IDCStatsContext *statsContext,
                      IDCMetaContext *metaContext)
    {
        indexCtrl->init();
        scoresContext->reset(metaContext->get().initRemScore);
        statsContext->reset();
        metaContext->set(IDCMetaContext::Initialized);
    }
};

#endif // DCRESETCONTEXTS_H
