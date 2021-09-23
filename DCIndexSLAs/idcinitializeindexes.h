#ifndef IDCINITIALIZEINDEXES_H
#define IDCINITIALIZEINDEXES_H

#include "DCIndexSLAs/idcindexes.h"
#include "DCIndexSLAs/idcindexservice.h"

class IDCInitializeIndexes
{
public:
    virtual void initialize(const DCContext::IDCIndexes *indexes, IDCIndexService *service) const = 0;
};
#endif // IINITIALIZEINDEXES_H
