#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
#include "abstractdcreqindexbuilder.h"
#include <DartsModelsContext/IndexesSLAs/idcidxbuilder.h>
class DCIndexSLAs
{
public:
    AbstractDCIdxCtrl *idxCtrl() const
    {
        return _indexController;
    }
    void setIndexCtrl(AbstractDCIdxCtrl *service)
    {
        _indexController = service;
    }
    AbstractDCReqIndexBuilder *reqIndexBuilder() const
    {
        return _reqIndexBuilder;
    }
    void setReqIndexBuilder(AbstractDCReqIndexBuilder *newReqIndexBuilder)
    {
        _reqIndexBuilder = newReqIndexBuilder;
    }
    IDCIdxBuilder *indexBuilder() const
    {
        return _indexBuilder;
    }
    void setIndexBuilder(IDCIdxBuilder *newIndexBuilder)
    {
        _indexBuilder = newIndexBuilder;
    }
private:
    IDCIdxBuilder *_indexBuilder;
    AbstractDCIdxCtrl* _indexController = nullptr;
    AbstractDCReqIndexBuilder *_reqIndexBuilder;
};
#endif // DCINDEXSLAS_H
