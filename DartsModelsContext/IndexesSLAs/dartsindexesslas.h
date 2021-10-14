#ifndef DARTSINDEXESSLAS_H
#define DARTSINDEXESSLAS_H

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
private:
    IUpdateDartsIndexes *_updateIndexes;
};
#endif // DARTSINDEXESSLAS_H
