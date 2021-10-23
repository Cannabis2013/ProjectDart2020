#ifndef IDCINDEXREDO_H
#define IDCINDEXREDO_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
class IDCIndexRedo
{
public:
    virtual void redo(IDCIndexController *indexService, IDCScoresService *scoresService) const = 0;
};
#endif // IDCINDEXREDO_H
