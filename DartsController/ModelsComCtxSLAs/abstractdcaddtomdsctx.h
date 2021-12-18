#ifndef ABSTRACTDCADDTOMDSCTX_H
#define ABSTRACTDCADDTOMDSCTX_H
class AbsDartsCtx;
class DCMeta;
class DCInput;
class DCIndex;
class IDCIdxBuilder;
class AbstractDCIptConverter;
class AbstractDCAddToMdsCtx
{
public:
    AbstractDCAddToMdsCtx(AbstractDCIptConverter *iptCvt, IDCIdxBuilder *idxCvt):
        _iptCvt(iptCvt),_idxCvt(idxCvt){}
    virtual bool add(DCInput &input, const DCIndex &idx, const DCMeta &meta,AbsDartsCtx *mdsCtx) = 0;
    AbstractDCIptConverter *iptCvt() const {return _iptCvt;}
    IDCIdxBuilder *idxCvt() const{return _idxCvt;}
private:
    AbstractDCIptConverter *_iptCvt;
    IDCIdxBuilder *_idxCvt;
};
#endif // ABSTRACTDCADDTOMDSCTX_H
