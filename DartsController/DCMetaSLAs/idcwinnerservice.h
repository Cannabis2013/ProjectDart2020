#ifndef IDCWINNERSERVICE_H
#define IDCWINNERSERVICE_H

#include <quuid.h>
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCPlayerServices/dcplayer.h"
class IDCWinnerService
{
public:
    virtual void set(const DCPlayer &winner) = 0;
    virtual void set(const DCInput &input) = 0;
    virtual DCPlayer &get() = 0;
};
#endif // USERSCORESCONTROLLERINTERFACE_H
