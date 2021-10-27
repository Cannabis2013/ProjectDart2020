#ifndef IDCCALCSCORE_H
#define IDCCALCSCORE_H

#include "DartsController/DCInputServices/dcinput.h"
class IDCCalcScore
{
public:
    virtual int getScore(const DCInput &input) const = 0;

};

#endif // IDCCALCSCORE_H
