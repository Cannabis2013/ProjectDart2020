#ifndef IDCGETSCORE_H
#define IDCGETSCORE_H

#include "DartsController/DCInputServices/dcinput.h"
class IDCGetScore
{
public:
    virtual int getScore(const DCInput &input) const = 0;

};

#endif // IDCGETSCORE_H
