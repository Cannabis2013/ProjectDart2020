#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H
#include "DartsController/DCIndexSLAs/idcidxctrl.h"
#include <DartsModelsContext/IndexesSLAs/idcidxbuilder.h>
class DCIndexSLAs
{
public:
    IDCIdxCtrl *idxCtrl() const {return _indexController;}
    void setIndexCtrl(IDCIdxCtrl *service) {_indexController = service;}
    IDCIdxBuilder *idxConverter() const {return _idxConverter;}
    void setIdxConverter(IDCIdxBuilder *converter) {_idxConverter = converter;}
private:
    IDCIdxBuilder *_idxConverter;
    IDCIdxCtrl* _indexController = nullptr;
};
#endif // DCINDEXSLAS_H
