#ifndef DCJSONSLAS_H
#define DCJSONSLAS_H
#include "DartsController/DCInputSLAs/idcinputjsoncontext.h"
#include "DartsController/DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
#include "DartsController/DCJsonSLAs/iaddplayernamestojson.h"
#include "DartsController/DCPlayerSLAs/idcplayerjsonbuilder.h"
#include "DartsController/DCIndexSLAs/idcindexestojson.h"
#include "icreatejsonobject.h"
#include "idccreatebytearray.h"
class IAddPlayerNamesToJson;
class DCJsonSLAs
{
public:
    IAddPlayerNamesToJson *addPlayerNamesToJson() const
    {
        return _addPlayerNamesToJson;
    }
    void setAddPlayerNamesToJson(IAddPlayerNamesToJson *service)
    {
        _addPlayerNamesToJson = service;
    }
    IAddTotalScoreToDartsInputsJson *addTotalScoresToJson() const
    {
        return _addTotalScoresToJson;
    }
    void setAddTotalScoresToJson(IAddTotalScoreToDartsInputsJson *service)
    {
        _addTotalScoresToJson = service;
    }
    IDCCreateByteArray *createByteArray() const
    {
        return _createByteArray;
    }
    void setCreateByteArray(IDCCreateByteArray *service)
    {
        _createByteArray = service;
    }
    ICreateJsonObject *createEmptyJsonObject() const
    {
        return _createEmptyJsonObject;
    }
    void setCreateEmptyJsonObject(ICreateJsonObject *service)
    {
        _createEmptyJsonObject = service;
    }
private:
    IAddPlayerNamesToJson *_addPlayerNamesToJson;
    IAddTotalScoreToDartsInputsJson *_addTotalScoresToJson;
    IDCCreateByteArray *_createByteArray;
    ICreateJsonObject *_createEmptyJsonObject;
};
#endif // DSJSONSERVICES_H
