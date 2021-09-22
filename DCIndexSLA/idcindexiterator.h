#ifndef IDCINDEXITERATOR_H
#define IDCINDEXITERATOR_H

#include "DCIndexSLA/idcindexservice.h"
#include "idcscoresservice.h"

class IDCIndexIterator
{
public:
    virtual void next(IDCIndexService *indexService, IDCScoresService *scoresService) const = 0;
};
#endif // IDCINDEXITERATOR_H
