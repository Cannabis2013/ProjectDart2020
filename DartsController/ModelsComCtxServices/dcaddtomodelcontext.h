#ifndef DCADDTOMODELCONTEXT_H
#define DCADDTOMODELCONTEXT_H
#include "DartsController/ModelsComCtxSLAs/abstractdcaddtomdsctx.h"
class DCAddToModelsContext : public AbstractDCAddToMdsCtx
{
public:
    DCAddToModelsContext(AbstractDCIptConverter *iptCvt, IDCIdxConverter *idxCvt):
        AbstractDCAddToMdsCtx(iptCvt,idxCvt){}
    virtual bool add(DCInput &input, const DCIndex &idx, const DCMeta &meta, AbstractDartsContext *mdsCtx) override
    {
        auto cvtdIdx = idxCvt()->convert(idx);
        auto cvtdIpt = iptCvt()->convert(input);
        auto r1 = mdsCtx->addInput(meta.tournamentId,cvtdIpt);
        auto r2 = mdsCtx->updateTournamentIndex(meta.tournamentId,cvtdIdx);
        return r1 && r2;
    }
};

#endif // DCADDTOMODELCONTEXT_H
