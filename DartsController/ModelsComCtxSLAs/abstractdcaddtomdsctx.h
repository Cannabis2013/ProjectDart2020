#ifndef ABSTRACTDCADDTOMDSCTX_H
#define ABSTRACTDCADDTOMDSCTX_H
#include "DartsController/DCInputSLAs/dcinput.h"
#include "DartsController/DCIndexSLAs/idcidxctrl.h"
#include "DartsModelsContext/SLAs/abstractdartscontext.h"
#include "DartsController/DCInputSLAs/abstractdciptconverter.h"
class AbstractDCAddToMdsCtx
{
public:
    AbstractDCAddToMdsCtx(IDCIdxCtrl *idxCtrl, AbstractDCIptConverter *iptCvt,
                          IDCMetaContext *metaCtx, IDCIdxConverter *idxCvt):
        _idxCtrl(idxCtrl),_iptCvt(iptCvt), _metaCtx(metaCtx),_idxCvt(idxCvt){}
    virtual bool add(DCInput &input, const DCIndex &idx, AbstractDartsContext *mdsCtx) = 0;
    IDCIdxCtrl *idxCtrl() const {return _idxCtrl;}
    AbstractDCIptConverter *iptCvt() const {return _iptCvt;}
    IDCMetaContext *metaCtx() const {return _metaCtx;}
    IDCIdxConverter *idxCvt() const{return _idxCvt;}
private:
    IDCIdxCtrl *_idxCtrl;
    AbstractDCIptConverter *_iptCvt;
    IDCMetaContext *_metaCtx;
    IDCIdxConverter *_idxCvt;
};
#endif // ABSTRACTDCADDTOMDSCTX_H
