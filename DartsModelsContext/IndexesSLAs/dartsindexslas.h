#ifndef DARTSINDEXSLAS_H
#define DARTSINDEXSLAS_H

#include "iresetdartsindexes.h"
#include "iupdatedartsindexes.h"

class DartsIndexSLAs
{
public:
    IUpdateDartsIndexes *updateIndexes() const
    {
        return _updateIndexes;
    }
    void setUpdateIndexes(IUpdateDartsIndexes *updateService)
    {
        _updateIndexes = updateService;
    }
    IResetDartsIndexes *resetIndexes() const
    {
        return _resetIndexes;
    }
    void setResetIndexes(IResetDartsIndexes *newResetIndexes)
    {
        _resetIndexes = newResetIndexes;
    }
private:
    IResetDartsIndexes *_resetIndexes;
    IUpdateDartsIndexes *_updateIndexes;
};
#endif // DARTSINDEXSLAS_H
