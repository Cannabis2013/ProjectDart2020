#ifndef IDCINDEXREDO_H
#define IDCINDEXREDO_H
#include "DCIndexSLA/idcindexservice.h"
#include "idcscoresservice.h"
class IDCIndexRedo
{
public:
    virtual void redo(IDCIndexService *indexService, IDCScoresService *scoresService) const = 0;
};
#endif // IDCINDEXREDO_H
