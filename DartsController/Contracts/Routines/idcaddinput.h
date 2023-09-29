#ifndef IDCADDINPUT_H
#define IDCADDINPUT_H

#include <DartsController/Contracts/Controller/idartsctrl.h>

class DCServices;
class QByteArray;
class AbstractDartsContext;
struct DCInput;
class IDCAddInput
{
public:
    virtual QByteArray add(const QByteArray &inputByteArray, IDartsCtrl *services) = 0;
};
#endif // ABSTRACTDCADDTOMDSCTX_H
