#ifndef IDCUNDOINDEX_H
#define IDCUNDOINDEX_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
class IDCUndoIndex
{
public:
    virtual void undo(IDCIndexController *indexService, IDCScoresService *scoresService) const = 0;
};
#endif // IDCUNDOINDEX_H
