#ifndef DCJSONSERVICES_H
#define DCJSONSERVICES_H
#include "DartsController/DCInputSLAs/idcinputstojson.h"
#include "DartsController/DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
#include "DartsController/DCJsonSLAs/iaddplayernamestojson.h"
#include "DartsController/DCPlayerSLAs/icreatejsonfromdcplayer.h"
#include "DartsController/DCJsonSLAs/idccreatejsonresponse.h"
#include "DartsController/DCIndexSLAs/idcindexestojson.h"
#include "DartsController/DCJsonSLAs/ijsonvaluesextractor.h"
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
    IDCJsonResponseBuilder *responseBuilder() const
    {
        return _responseBuilder;
    }
    void setResponseBuilderService(IDCJsonResponseBuilder *newResponseBuilder)
    {
        _responseBuilder = newResponseBuilder;
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
private:
    IAddPlayerNamesToJson *_addPlayerNamesToJson;
    IAddTotalScoreToDartsInputsJson *_addTotalScoresToJson;
    IJsonValuesExtractor *_jsonExtractor;
    IDCJsonResponseBuilder *_responseBuilder;
};
#endif // DSJSONSERVICES_H
