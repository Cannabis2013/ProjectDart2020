#ifndef DCADDTOMODELCONTEXT_H
#define DCADDTOMODELCONTEXT_H
#include "DartsController/ModelsComCtxSLAs/abstractdcaddtomdsctx.h"
class DCAddToModelsContext : public AbstractDCAddToMdsCtx
{
public:
    DCAddToModelsContext(IDCIdxCtrl *idxCtrl, AbstractDCIptConverter *iptCvt,
                         IDCMetaContext *metaCtx, IDCIdxConverter *idxCvt):
        AbstractDCAddToMdsCtx(idxCtrl,iptCvt,metaCtx,idxCvt){}
    virtual bool add(DCInput &input, const DCIndex &idx, AbstractDartsContext *mdsCtx) override
    {
        auto cvtdIdx = idxCvt()->convert(idx);
        auto cvtdIpt = iptCvt()->convert(input);
        auto r1 = mdsCtx->addInput(metaCtx()->get().tournamentId,cvtdIpt);
        auto r2 = mdsCtx->updateTournamentIndex(metaCtx()->get().tournamentId,cvtdIdx);
        return r1 && r2;
    }
};

#endif // DCADDTOMODELCONTEXT_H
