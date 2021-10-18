#ifndef IDCINITIALIZEINDEXES_H
#define IDCINITIALIZEINDEXES_H

#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCIndexServices/dcindexes.h"

class IDCInitializeIndexes
{
public:
    virtual void initialize(const DCIndexes &indexes, IDCIndexService *service) const = 0;
};
#endif // IINITIALIZEINDEXES_H
