#ifndef IDCGETSCORE_H
#define IDCGETSCORE_H
#include "idcmodel.h"
class IDCgetScore
{
public:
    virtual int getScore(const DCContext::IDCModel *inputModel) const = 0;
};
#endif // IDCCALCULATESCORE_H
