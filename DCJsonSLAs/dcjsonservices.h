#ifndef DCJSONSERVICES_H
#define DCJSONSERVICES_H
#include "DCInputSLAs/idcinputstojson.h"
#include "DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
#include "DCJsonSLAs/iaddplayernamestojson.h"
#include "DCPlayerSLAs/icreatejsonfromdcplayer.h"
#include "DCJsonSLAs/idccreatejsonresponse.h"
#include "DCIndexSLAs/idcindexestojson.h"
#include "DCJsonSLAs/ijsonvaluesextractor.h"
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
