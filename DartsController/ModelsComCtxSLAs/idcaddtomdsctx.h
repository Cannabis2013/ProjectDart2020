#ifndef IDCADDTOMDSCTX_H
#define IDCADDTOMDSCTX_H
class QByteArray;
class QJsonObject;
class AbsDartsCtx;
struct DCMeta;
struct DCInput;
struct DCIndex;
class IDCIndexConverter;
template<typename T, typename U, typename V>
class IDCInputBuilder;
class IDCAddToMdsCtx
{
public:
    typedef DCInput Input;
    typedef IDCInputBuilder<Input,QByteArray,QJsonObject> InputBuilder;
    virtual bool add(DCInput &ipt, const DCIndex &idx, const DCMeta &meta,
                     AbsDartsCtx *mdsCtx, InputBuilder *cvtr, IDCIndexConverter *_idxCvt) = 0;
};
#endif // ABSTRACTDCADDTOMDSCTX_H
