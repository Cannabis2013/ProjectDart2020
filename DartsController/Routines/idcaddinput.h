#ifndef IDCADDINPUT_H
#define IDCADDINPUT_H
class QByteArray;
class AbsDartsCtx;
struct DCInput;
class IDCAddInput
{
public:
    virtual QByteArray add(const QByteArray &inputByteArray) = 0;
};
#endif // ABSTRACTDCADDTOMDSCTX_H