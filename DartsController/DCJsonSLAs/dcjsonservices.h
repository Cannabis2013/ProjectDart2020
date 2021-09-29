#ifndef DCJSONSERVICES_H
#define DCJSONSERVICES_H
#include "DartsController/DCInputSLAs/idcinputstojson.h"
#include "DartsController/DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
#include "DartsController/DCJsonSLAs/iaddplayernamestojson.h"
#include "DartsController/DCPlayerSLAs/icreatejsonfromdcplayer.h"
#include "DartsController/DCIndexSLAs/idcindexestojson.h"
#include "DartsController/DCJsonSLAs/ijsonvaluesextractor.h"
#include "icreatejsonobject.h"
#include "idccreatebytearray.h"
class IAddPlayerNamesToJson;
class DCJsonServices
{
public:
    IAddPlayerNamesToJson *addPlayerNamesToJson() const
    {
        return _addPlayerNamesToJson;
    }
    void setAddPlayerNamesToJson(IAddPlayerNamesToJson *newAddPlayerNamesToJson)
    {
        _addPlayerNamesToJson = newAddPlayerNamesToJson;
    }
    IJsonValuesExtractor *jsonExtractor() const
    {
        return _jsonExtractor;
    }
    void setJsonExtractor(IJsonValuesExtractor *newJsonExtractor)
    {
        _jsonExtractor = newJsonExtractor;
    }
    IAddTotalScoreToDartsInputsJson *addTotalScoresToJson() const
    {
        return _addTotalScoresToJson;
    }
    void setAddTotalScoresToJson(IAddTotalScoreToDartsInputsJson *newAddTotalScoresToJson)
    {
        _addTotalScoresToJson = newAddTotalScoresToJson;
    }
    IDCCreateByteArray *createByteArray() const
    {
        return _createByteArray;
    }
    void setCreateByteArray(IDCCreateByteArray *newCreateByteArray)
    {
        _createByteArray = newCreateByteArray;
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
    IJsonValuesExtractor *_jsonExtractor;
    IDCCreateByteArray *_createByteArray;
    ICreateJsonObject *_createEmptyJsonObject;
};
#endif // DSJSONSERVICES_H
