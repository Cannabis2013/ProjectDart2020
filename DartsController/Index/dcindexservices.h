#ifndef DCINDEXSERVICES_H
#define DCINDEXSERVICES_H

#include "idcindexcontroller.h"
#include <DartsController/Converters/idcmodeltojson.h>

struct DCMeta;
struct DCIndex;

class DCIndexServices
{
public:
    typedef IDCModelToJson<DCIndex> IndexToJson;
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    IndexController *indexController() const {return _indexController;}
    void setIndexController(IndexController *service) {_indexController = service;}
    IndexToJson *indexToJson() const {return _indexConverter;}
    void setIndexToByteArray(IndexToJson *converter) {_indexConverter = converter;}
private:
    IndexToJson *_indexConverter;
    IndexController *_indexController = nullptr;
};
#endif // DCINDEXSERVICES_H
