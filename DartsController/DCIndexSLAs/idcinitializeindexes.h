#ifndef IDCINITIALIZEINDEXES_H
#define IDCINITIALIZEINDEXES_H

#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCIndexServices/dcindex.h"

class IDCInitializeIndexes
{
public:
    virtual void initialize(const DCIndex &indexes, IDCIndexController *service) const = 0;
};
#endif // IINITIALIZEINDEXES_H
