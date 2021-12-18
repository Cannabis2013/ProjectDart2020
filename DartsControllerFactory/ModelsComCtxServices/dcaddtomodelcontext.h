#ifndef DCADDTOMODELCONTEXT_H
#define DCADDTOMODELCONTEXT_H
#include "ModelsComCtxSLAs/abstractdcaddtomdsctx.h"
#include "DCInputSLAs/abstractdciptconverter.h"
#include "Models/dcinput.h"
#include "SLAs/absdartsctx.h"
#include "ConverterSLAs/idcidxbuilder.h"
#include "TournamentModels/tnmvalues.h"
#include "Models/dcindex.h"
#include "Models/dcmeta.h"
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
