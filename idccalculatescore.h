#ifndef IDCCALCULATESCORE_H
#define IDCCALCULATESCORE_H

#include "idcinputmodel.h"

class IDCCalculateScore
{
public:
    virtual int getScore(const DCContext::IDCInputModel *inputModel) const = 0;
};

#endif // IDCCALCULATESCORE_H
