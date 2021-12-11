#ifndef ABSTRACTDCADDTOMDSCTX_H
#define ABSTRACTDCADDTOMDSCTX_H
#include "DartsController/DCInputSLAs/dcinput.h"
#include "DartsController/DCIndexSLAs/idcidxctrl.h"
#include "DartsModelsContext/SLAs/absdartsctx.h"
#include "DartsController/DCInputSLAs/abstractdciptconverter.h"
class AbstractDCAddToMdsCtx
{
public:
    AbstractDCAddToMdsCtx(AbstractDCIptConverter *iptCvt, IDCIdxConverter *idxCvt):
        _iptCvt(iptCvt),_idxCvt(idxCvt){}
    virtual bool add(DCInput &input, const DCIndex &idx, const DCMeta &meta,AbsDartsCtx *mdsCtx) = 0;
    AbstractDCIptConverter *iptCvt() const {return _iptCvt;}
    IDCIdxConverter *idxCvt() const{return _idxCvt;}
private:
    AbstractDCIptConverter *_iptCvt;
    IDCIdxConverter *_idxCvt;
};
#endif // ABSTRACTDCADDTOMDSCTX_H
