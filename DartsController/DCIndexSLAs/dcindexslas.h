#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H
#include "DCIndexSLAs/idcindexcontroller.h"
#include "idcindexconverter.h"
class DCIndexSLAs
{
public:
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    IndexController *indexService() const {return _indexController;}
    void setIndexCtrl(IndexController *service) {_indexController = service;}
    IDCIndexConverter *idxConverter() const {return _idxConverter;}
    void setIndexConverter(IDCIndexConverter *converter) {_idxConverter = converter;}
private:
    IDCIndexConverter *_idxConverter;
    IndexController *_indexController = nullptr;
};
#endif // DCINDEXSLAS_H