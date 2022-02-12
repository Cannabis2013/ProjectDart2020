#ifndef DCINDEXSLAS_H
#define DCINDEXSLAS_H
#include "DCIndexSLAs/idcindexcontroller.h"
#include "idcindexconverter.h"
class DCIndexSLAs
{
public:
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    IndexController *indexController() const {return _indexController;}
    void setIndexController(IndexController *service) {_indexController = service;}
    IDCIndexConverter *indexToByteArray() const {return _idxConverter;}
    void setIndexToByteArray(IDCIndexConverter *converter) {_idxConverter = converter;}
private:
    IDCIndexConverter *_idxConverter;
    IndexController *_indexController = nullptr;
};
#endif // DCINDEXSLAS_H
