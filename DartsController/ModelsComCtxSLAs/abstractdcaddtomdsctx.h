#ifndef ABSTRACTDCADDTOMDSCTX_H
#define ABSTRACTDCADDTOMDSCTX_H
#include "DartsController/DCInputSLAs/dcinput.h"
#include "DartsController/DCIndexSLAs/absdcidxctrl.h"
#include "DartsModelsContext/SLAs/abstractdartscontext.h"
#include "DartsController/DCInputSLAs/abstractdciptconverter.h"
class AbstractDCAddToMdsCtx
{
public:
    AbstractDCAddToMdsCtx(AbsDCIdxCtrl *idxCtrl, AbstractDCIptConverter *iptCvt,
                          IDCMetaContext *metaCtx, IDCIdxConverter *idxCvt):
        _idxCtrl(idxCtrl),_iptCvt(iptCvt), _metaCtx(metaCtx),_idxCvt(idxCvt){}
    virtual bool add(DCInput &input, AbstractDartsContext *mdsCtx) = 0;
    AbsDCIdxCtrl *idxCtrl() const {return _idxCtrl;}
    AbstractDCIptConverter *iptCvt() const {return _iptCvt;}
    IDCMetaContext *metaCtx() const {return _metaCtx;}
    IDCIdxConverter *idxCvt() const{return _idxCvt;}
private:
    AbsDCIdxCtrl *_idxCtrl;
    AbstractDCIptConverter *_iptCvt;
    IDCMetaContext *_metaCtx;
    IDCIdxConverter *_idxCvt;
};
#endif // ABSTRACTDCADDTOMDSCTX_H
