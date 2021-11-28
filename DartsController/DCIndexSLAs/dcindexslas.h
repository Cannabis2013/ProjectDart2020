#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
#include "abstractdcreqidxbuilder.h"
#include <DartsModelsContext/IndexesSLAs/idcidxconverter.h>
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
    AbstractDCReqIdxBuilder *reqIndexBuilder() const
    {
        return _reqIndexBuilder;
    }
    void setReqIndexBuilder(AbstractDCReqIdxBuilder *newReqIndexBuilder)
    {
        _reqIndexBuilder = newReqIndexBuilder;
    }
    IDCIdxConverter *idxConverter() const
    {
        return _idxConverter;
    }
    void setIdxConverter(IDCIdxConverter *newIndexBuilder)
    {
        _idxConverter = newIndexBuilder;
    }
private:
    IDCIdxConverter *_idxConverter;
    AbstractDCIdxCtrl* _indexController = nullptr;
    AbstractDCReqIdxBuilder *_reqIndexBuilder;
};
#endif // DCINDEXSLAS_H
