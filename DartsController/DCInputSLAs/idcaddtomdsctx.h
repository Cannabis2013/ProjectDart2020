#ifndef IDCADDTOMDSCTX_H
#define IDCADDTOMDSCTX_H
class QByteArray;
class AbsDartsCtx;
struct DCInput;
class IDCAddToMdsCtx
{
public:
    virtual DCInput add(const QByteArray &inputByteArray) = 0;
};
#endif // ABSTRACTDCADDTOMDSCTX_H
