#ifndef DARTSINDEXESDBSLAS_H
#define DARTSINDEXESDBSLAS_H

#include "icreatedartsinexesmodels.h"
#include "idartsindexesdbcontext.h"
#include "idartsindexesjsonbuilder.h"
#include "igetdartsindexesmodel.h"
#include "iremovedartsindexes.h"
class DartsIndexesDbSLAs
{
public:
    IDartsIndexesBuilder *indexesBuilder() const
    {
        return _indexesBuilder;
    }
    void setIndexesBuilder(IDartsIndexesBuilder *builder)
    {
        _indexesBuilder = builder;
    }
    IDartsIndexesJsonBuilder *indexesJsonBuilder() const
    {
        return _indexesJsonBuilder;
    }
    void setIndexesJsonBuilder(IDartsIndexesJsonBuilder *builder)
    {
        _indexesJsonBuilder = builder;
    }
    IGetDartsIndexesModel *getIndexesModel() const
    {
        return _getIndexesModel;
    }
    void setGetIndexesModel(IGetDartsIndexesModel *service)
    {
        _getIndexesModel = service;
    }
    IDartsIndexesDbContext *indexesDbContext() const
    {
        return _indexesDbContext;
    }
    void setIndexesDbContext(IDartsIndexesDbContext *dbContext)
    {
        _indexesDbContext = dbContext;
    }
    IRemoveDartsIndexes *removeIndexes() const
    {
        return _removeIndexes;
    }
    void setRemoveIndexes(IRemoveDartsIndexes *newRemoveIndexes)
    {
        _removeIndexes = newRemoveIndexes;
    }
private:
    IRemoveDartsIndexes *_removeIndexes;
    IDartsIndexesDbContext *_indexesDbContext;
    IGetDartsIndexesModel *_getIndexesModel;
    IDartsIndexesBuilder *_indexesBuilder;
    IDartsIndexesJsonBuilder *_indexesJsonBuilder;
};
#endif // DARTSINDEXESDBSLAS_H
