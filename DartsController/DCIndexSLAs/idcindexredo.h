#ifndef IDCINDEXREDO_H
#define IDCINDEXREDO_H
#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
class IDCIndexRedo
{
public:
    virtual void redo(IDCIndexService *indexService, IDCScoresService *scoresService) const = 0;
};
#endif // IDCINDEXREDO_H
