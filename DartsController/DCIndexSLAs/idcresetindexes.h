#ifndef IDCRESETINDEXES_H
#define IDCRESETINDEXES_H
#include "DartsController/DCIndexSLAs/idcindexservice.h"
class IDCResetIndexes
{
public:
    virtual void reset(IDCIndexService *indexService) const = 0;
};
#endif // IDCRESETINDEXES_H
