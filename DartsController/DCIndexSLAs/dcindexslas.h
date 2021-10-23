#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCIndexSLAs/idcinputindexbuilder.h"
#include "DartsController/DCIndexSLAs/idcindexiterator.h"
#include "DartsController/DCIndexSLAs/idcindexredo.h"
#include "DartsController/DCIndexSLAs/idcinitializeindexes.h"
#include "DartsController/DCIndexSLAs/idcresetindexes.h"
#include "DartsController/DCIndexSLAs/idcundoindex.h"
#include "DartsController/DCIndexSLAs/IDCIndexesJsonKeys.h"
#include "idcreqinputindexbuilder.h"
class DCIndexSLAs
{
public:
    IDCIndexController *indexController() const
    {
        return _indexService;
    }
    void setIndexService(IDCIndexController *service)
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
    IDCInputIndexBuilder *inputIndexBuilder() const
    {
        return _inputIndexBuilder;
    }
    void setIndexesBuilder(IDCInputIndexBuilder *service)
    {
        _inputIndexBuilder = service;
    }
    IDCIndexesJsonKeys *indexKeys() const
    {
        return _indexKeys;
    }
    void setIndexKeys(IDCIndexesJsonKeys *service)
    {
        _indexKeys = service;
    }
    IDCReqInputIndexBuilder *reqIndexBuilder() const
    {
        return _reqIndexBuilder;
    }
    void setReqIndexBuilder(IDCReqInputIndexBuilder *newReqIndexBuilder)
    {
        _reqIndexBuilder = newReqIndexBuilder;
    }
private:
    IDCIndexController* _indexService = nullptr;
    IDCIndexIterator *_indexIterator;
    IDCUndoIndex * _undoIndex;
    IDCIndexRedo *_redoIndex;
    IDCResetIndexes *_resetIndexes;
    IDCInitializeIndexes *_initializeIndexes;
    IDCInputIndexBuilder* _inputIndexBuilder;
    IDCReqInputIndexBuilder *_reqIndexBuilder;
    IDCIndexesJsonKeys *_indexKeys;
};
#endif // DCINDEXSLAS_H
