#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H
#include "DartsController/DCIndexSLAs/idcidxctrl.h"
#include <DartsModelsContext/IndexesSLAs/idcidxconverter.h>
class DCIndexSLAs
{
public:
    IDCIdxCtrl *idxCtrl() const
    {
        return _indexController;
    }
    void setIndexCtrl(IDCIdxCtrl *service)
    {
        _indexController = service;
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
    IDCIdxCtrl* _indexController = nullptr;
};
#endif // DCINDEXSLAS_H
