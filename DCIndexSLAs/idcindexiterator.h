#ifndef IDCINDEXITERATOR_H
#define IDCINDEXITERATOR_H

#include "DCIndexSLAs/idcindexservice.h"
#include "DCScoresSLAs/idcscoresservice.h"

class IDCIndexIterator
{
public:
    virtual void next(IDCIndexService *indexService, IDCScoresService *scoresService) const = 0;
};
#endif // IDCINDEXITERATOR_H
