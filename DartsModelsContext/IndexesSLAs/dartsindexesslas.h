#ifndef DARTSINDEXESSLAS_H
#define DARTSINDEXESSLAS_H

#include "iresetdartsindexes.h"
#include "iupdatedartsindexes.h"

class DartsIndexesSLAs
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
#endif // DARTSINDEXESSLAS_H
