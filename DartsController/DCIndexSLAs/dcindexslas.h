#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCIndexSLAs/idcindexbuilder.h"
#include "idcreqinputindexbuilder.h"
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
    IDCIndexBuilder *indexBuilder() const
    {
        return _indexBuilder;
    }
    void setIndexBuilder(IDCIndexBuilder *service)
    {
        _indexBuilder = service;
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
    IDCIndexController* _indexController = nullptr;
    IDCIndexBuilder* _indexBuilder;
    IDCReqInputIndexBuilder *_reqIndexBuilder;
};
#endif // DCINDEXSLAS_H
