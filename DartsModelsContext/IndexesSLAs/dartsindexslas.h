#ifndef DARTSINDEXSLAS_H
#define DARTSINDEXSLAS_H
#include "idartsindexbuilder.h"
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
    IResetDartsIndexes *resetDartsIndexes() const
    {
        return _resetIndexes;
    }
    void setResetIndexes(IResetDartsIndexes *newResetIndexes)
    {
        _resetIndexes = newResetIndexes;
    }
    IDartsIndexBuilder *indexBuilder() const
    {
        return _indexBuilder;
    }
    void setIndexBuilder(IDartsIndexBuilder *newIndexBuilder)
    {
        _indexBuilder = newIndexBuilder;
    }
private:
    IDartsIndexBuilder *_indexBuilder;
    IResetDartsIndexes *_resetIndexes;
    IUpdateDartsIndexes *_updateIndexes;
};
#endif // DARTSINDEXSLAS_H
