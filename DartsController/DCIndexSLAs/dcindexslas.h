#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H

#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCIndexSLAs/idcindexesbuilder.h"
#include "DartsController/DCIndexSLAs/idcindexiterator.h"
#include "DartsController/DCIndexSLAs/idcindexredo.h"
#include "DartsController/DCIndexSLAs/idcinitializeindexes.h"
#include "DartsController/DCIndexSLAs/idcresetindexes.h"
#include "DartsController/DCIndexSLAs/idcundoindex.h"
#include "DartsController/DCIndexSLAs/idcindexestojson.h"
#include "DartsController/DCIndexSLAs/IDCIndexesJsonKeys.h"

class DCIndexSLAs
{
public:
    IDCIndexService *indexService() const
    {
        return _indexService;
    }
    void setIndexService(IDCIndexService *service)
    {
        _indexService = service;
    }
    IDCIndexIterator *indexIterator() const
    {
        return _indexIterator;
    }
    void setIndexIterator(IDCIndexIterator *service)
    {
        _indexIterator = service;
    }
    IDCResetIndexes *resetIndexes() const
    {
        return _resetIndexes;
    }
    void setResetIndexes(IDCResetIndexes *service)
    {
        _resetIndexes = service;
    }
    IDCUndoIndex *undoIndex() const
    {
        return _undoIndex;
    }
    void setUndoIndex(IDCUndoIndex *service)
    {
        _undoIndex = service;
    }
    IDCIndexRedo *indexRedo() const
    {
        return _redoIndex;
    }
    void setRedoIndex(IDCIndexRedo *service)
    {
        _redoIndex = service;
    }
    IDCInitializeIndexes *initializeIndexes() const
    {
        return _initializeIndexes;
    }
    void setInitializeIndexes(IDCInitializeIndexes *service)
    {
        _initializeIndexes = service;
    }
    IDCIndexesBuilder *indexesBuilder() const
    {
        return _dartsIndexesBuilderService;
    }
    void setIndexesBuilder(IDCIndexesBuilder *service)
    {
        _dartsIndexesBuilderService = service;
    }
    IDCIndexesToJson *indexesToJson() const
    {
        return _indexesToJson;
    }
    void setIndexesToJsonService(IDCIndexesToJson *service)
    {
        _indexesToJson = service;
    }
    IDCIndexesJsonKeys *indexKeys() const
    {
        return _indexKeys;
    }
    void setIndexKeys(IDCIndexesJsonKeys *service)
    {
        _indexKeys = service;
    }

private:
    IDCIndexService* _indexService = nullptr;
    IDCIndexIterator *_indexIterator;
    IDCUndoIndex * _undoIndex;
    IDCIndexRedo *_redoIndex;
    IDCResetIndexes *_resetIndexes;
    IDCInitializeIndexes *_initializeIndexes;
    IDCIndexesBuilder* _dartsIndexesBuilderService;
    IDCIndexesToJson *_indexesToJson;
    IDCIndexesJsonKeys *_indexKeys;
};
#endif // DCINDEXSLAS_H
