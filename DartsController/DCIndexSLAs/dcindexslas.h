#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "idcreqinputindexbuilder.h"
#include <DartsModelsContext/IndexesSLAs/idcindexbuilder.h>
class DCIndexSLAs
{
public:
    IDCIndexController *indexController() const
    {
        return _indexController;
    }
    void setIndexService(IDCIndexController *service)
    {
        _indexController = service;
    }
    IDCReqInputIndexBuilder *reqIndexBuilder() const
    {
        return _reqIndexBuilder;
    }
    void setReqIndexBuilder(IDCReqInputIndexBuilder *newReqIndexBuilder)
    {
        _reqIndexBuilder = newReqIndexBuilder;
    }
    IDCIndexBuilder *indexBuilder() const
    {
        return _indexBuilder;
    }
    void setIndexBuilder(IDCIndexBuilder *newIndexBuilder)
    {
        _indexBuilder = newIndexBuilder;
    }
private:
    IDCIndexBuilder *_indexBuilder;
    IDCIndexController* _indexController = nullptr;
    IDCReqInputIndexBuilder *_reqIndexBuilder;
};
#endif // DCINDEXSLAS_H
