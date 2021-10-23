#ifndef IDCINDEXITERATOR_H
#define IDCINDEXITERATOR_H

#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"

class IDCIndexIterator
{
public:
    virtual void next(IDCIndexController *indexService, IDCScoresService *scoresService) const = 0;
};
#endif // IDCINDEXITERATOR_H
