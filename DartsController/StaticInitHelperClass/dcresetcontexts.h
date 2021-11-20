#ifndef DCRESETCONTEXTS_H
#define DCRESETCONTEXTS_H
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "DartsController/PlayerStatsSLAs/idcstatscontext.h"
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCPlayerSLAs/IDCPlayerCtx.h"
class DCResetContexts
{
public:
    static void reset(AbstractDCIdxCtrl *indexCtrl, AbstractDCScoresCtx *scoresContext,
                      IDCStatsContext *statsContext, IDCMetaCtx *metaContext,
                      IDCPlayerCtx *playerController, IDartsStatusCodes *statusCodes)
    {
        indexCtrl->init();
        scoresContext->reset();
        statsContext->reset();
        metaContext->set(statusCodes->initialized());
        playerController->reset();
    }
};

#endif // DCRESETCONTEXTS_H
