#ifndef DCADDTOMODELCONTEXT_H
#define DCADDTOMODELCONTEXT_H
#include "DartsController/ModelsComCtxSLAs/abstractdcaddtomdsctx.h"
#include "DartsModelsContext//TournamentModels/tnmvalues.h"
#include "DartsController/DCInputSLAs/abstractdciptconverter.h"
#include "DartsController/DCInputSLAs/dcinput.h"
#include "DartsController/DCIndexSLAs/dcindex.h"
#include "DartsModelsContext/SLAs/absdartsctx.h"
#include "DartsModelsContext/IndexesSLAs/idcidxbuilder.h"
class DCAddToModelsContext : public AbstractDCAddToMdsCtx
{
public:
    DCAddToModelsContext(AbstractDCIptConverter *iptCvt, IDCIdxBuilder *idxCvt):
        AbstractDCAddToMdsCtx(iptCvt,idxCvt){}
    virtual bool add(DCInput &input, const DCIndex &idx, const DCMeta &meta, AbsDartsCtx *mdsCtx) override
    {
        auto cvtdIdx = idxCvt()->convert(idx);
        auto cvtdIpt = iptCvt()->convert(input);
        auto r1 = mdsCtx->addInput(meta.tournamentId,cvtdIpt);
        auto r2 = mdsCtx->updateTournamentIndex(meta.tournamentId,cvtdIdx);
        return r1 && r2;
    }
};

#endif // DCADDTOMODELCONTEXT_H
