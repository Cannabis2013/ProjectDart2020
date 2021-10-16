#ifndef IDCGETSCORE_H
#define IDCGETSCORE_H

#include "DartsController/DCInputSLAs/idcinput.h"

class IDCGetScore
{
public:
    virtual int getScore(const IDCInput *inputModel) const = 0;

};

#endif // IDCGETSCORE_H
