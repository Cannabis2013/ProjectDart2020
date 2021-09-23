#ifndef IDCGETSCORE_H
#define IDCGETSCORE_H

#include "DCInputSLAs/idcinputmodel.h"

class IDCGetScore
{
public:
    virtual int getScore(const DCContext::IDCInputModel *inputModel) const = 0;

};

#endif // IDCGETSCORE_H
