#ifndef IDCADDTOMDSCTX_H
#define IDCADDTOMDSCTX_H
class AbsDartsCtx;
struct DCInput;
class IDCAddToMdsCtx
{
public:
    virtual bool add(DCInput &ipt, AbsDartsCtx *mdsCtx) = 0;
};
#endif // ABSTRACTDCADDTOMDSCTX_H
