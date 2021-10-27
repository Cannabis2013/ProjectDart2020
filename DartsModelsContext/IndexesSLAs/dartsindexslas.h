#ifndef DARTSINDEXSLAS_H
#define DARTSINDEXSLAS_H
#include "idartsindexbuilder.h"
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
    IUpdateDartsIndexes *_updateIndexes;
};
#endif // DARTSINDEXSLAS_H
