#ifndef DCINDEXSERVICES_H
#define DCINDEXSERVICES_H

#include <idcindexiterator.h>
#include <idcindexredo.h>
#include <idcindexservice.h>
#include <idcresetindexes.h>
#include <idcundoindex.h>

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
private:
    IDCIndexService* _indexService = nullptr;
    IDCIndexIterator *_indexIterator;
    IDCUndoIndex * _undoIndex;
    IDCIndexRedo *_redoIndex;
    IDCResetIndexes *_resetIndexes;
};
#endif // DCINDEXSERVICES_H
