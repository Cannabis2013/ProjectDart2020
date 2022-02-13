#ifndef DCINDEXSERVICES_H
#define DCINDEXSERVICES_H
#include "DCIndexSLAs/idcindexcontroller.h"
#include "idcindextobytearray.h"
class DCIndexServices
{
public:
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    IndexController *indexController() const {return _indexController;}
    void setIndexController(IndexController *service) {_indexController = service;}
    IDCIndexToByteArray *indexToByteArray() const {return _indexConverter;}
    void setIndexToByteArray(IDCIndexToByteArray *converter) {_indexConverter = converter;}
private:
    IDCIndexToByteArray *_indexConverter;
    IndexController *_indexController = nullptr;
};
#endif // DCINDEXSERVICES_H
