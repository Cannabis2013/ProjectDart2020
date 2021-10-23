#ifndef IDCRESETINDEXES_H
#define IDCRESETINDEXES_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
class IDCResetIndexes
{
public:
    virtual void reset(IDCIndexController *indexService) const = 0;
};
#endif // IDCRESETINDEXES_H
