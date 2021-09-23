#ifndef IDCINITIALIZEINDEXES_H
#define IDCINITIALIZEINDEXES_H

#include "DartsController/DCIndexSLAs/idcindexes.h"
#include "DartsController/DCIndexSLAs/idcindexservice.h"

class IDCInitializeIndexes
{
public:
    virtual void initialize(const DCContext::IDCIndexes *indexes, IDCIndexService *service) const = 0;
};
#endif // IINITIALIZEINDEXES_H
