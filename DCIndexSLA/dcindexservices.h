#ifndef DCINDEXSERVICES_H
#define DCINDEXSERVICES_H

#include "DCIndexSLA/idcindexservice.h"
#include "DCIndexSLA/idcindexesbuilder.h"
#include "DCIndexSLA/idcindexiterator.h"
#include "DCIndexSLA/idcindexredo.h"
#include "DCIndexSLA/idcinitializeindexes.h"
#include "DCIndexSLA/idcresetindexes.h"
#include "DCIndexSLA/idcundoindex.h"

#include "DCIndexSLA/idcindexestojson.h"

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
