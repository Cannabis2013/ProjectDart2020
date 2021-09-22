#ifndef IDCGETSCORE_H
#define IDCGETSCORE_H
#include "DCInputsSLA/idcinputmodel.h"
class IDCgetScore
{
public:
    virtual int getScore(const DCContext::IDCInputModel *inputModel) const = 0;
};
#endif // IDCCALCULATESCORE_H
