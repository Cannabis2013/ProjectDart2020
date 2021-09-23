#ifndef DCINDEXSERVICES_H
#define DCINDEXSERVICES_H

#include "DCIndexSLAs/idcindexservice.h"
#include "DCIndexSLAs/idcindexesbuilder.h"
#include "DCIndexSLAs/idcindexiterator.h"
#include "DCIndexSLAs/idcindexredo.h"
#include "DCIndexSLAs/idcinitializeindexes.h"
#include "DCIndexSLAs/idcresetindexes.h"
#include "DCIndexSLAs/idcundoindex.h"
#include "DCIndexSLAs/idcindexestojson.h"

class DCIndexServices
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
    void setUndoIndex(IDCUndoIndex *newUndoIndex)
    {
        _undoIndex = newUndoIndex;
    }
    IDCIndexRedo *indexRedo() const
    {
        return _redoIndex;
    }
    void setRedoIndex(IDCIndexRedo *newRedoIndex)
    {
        _redoIndex = newRedoIndex;
    }
    IDCInitializeIndexes *initializeIndexes() const
    {
        return _initializeIndexes;
    }
    void setInitializeIndexes(IDCInitializeIndexes *newInitializeIndexes)
    {
        _initializeIndexes = newInitializeIndexes;
    }
    IDCIndexesBuilder *indexesBuilder() const
    {
        return _dartsIndexesBuilderService;
    }
    void setIndexesBuilder(IDCIndexesBuilder *newDartsIndexesBuilderService)
    {
        _dartsIndexesBuilderService = newDartsIndexesBuilderService;
    }
    IDCIndexesToJson *indexesToJson() const
    {
        return _indexesToJson;
    }
    void setIndexesToJsonService(IDCIndexesToJson *newIndexesToJson)
    {
        _indexesToJson = newIndexesToJson;
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

};
#endif // DCINDEXSERVICES_H
