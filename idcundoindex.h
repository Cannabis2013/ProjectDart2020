#ifndef IDCUNDOINDEX_H
#define IDCUNDOINDEX_H
#include <idcindexservice.h>
#include "idcscoresservice.h"
class IDCUndoIndex
{
public:
    virtual void undo(IDCIndexService *indexService, IDCScoresService *scoresService) const = 0;
};
#endif // IDCUNDOINDEX_H
