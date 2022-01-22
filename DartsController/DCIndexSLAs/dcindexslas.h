#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H
#include "DCIndexSLAs/idcindexcontroller.h"
class IDCIndexConverter;
class DCIndexSLAs
{
public:
    IDCIndexController *idxCtrl() const {return _indexController;}
    void setIndexCtrl(IDCIndexController *service) {_indexController = service;}
    IDCIndexConverter *idxConverter() const {return _idxConverter;}
    void setIndexConverter(IDCIndexConverter *converter) {_idxConverter = converter;}
private:
    IDCIndexConverter *_idxConverter;
    IDCIndexController* _indexController = nullptr;
};
#endif // DCINDEXSLAS_H
