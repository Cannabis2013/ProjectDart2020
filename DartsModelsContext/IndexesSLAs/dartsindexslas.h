#ifndef DARTSINDEXSLAS_H
#define DARTSINDEXSLAS_H
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
private:
    IUpdateDartsIndexes *_updateIndexes;
};
#endif // DARTSINDEXSLAS_H
