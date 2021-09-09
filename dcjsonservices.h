#ifndef DCJSONSERVICES_H
#define DCJSONSERVICES_H
#include <idcturnvaluestojson.h>
#include <idcinputstojson.h>
#include <iaddtotalscoretodartsinputsjson.h>
#include <iaddplayernamestojson.h>
#include <ijsonkeyplayer.h>
#include "icreatejsonfromdcplayer.h"
#include "idccreatejsonresponse.h"
#include "idcindexestojson.h"
#include "ijsonvaluesextractor.h"
class IAddPlayerNamesToJson;
class DCJsonServices
{
public:
    IDCInputsToJson *inputsToJson() const
    {
        return _jsonModelBuilderService;
    }
    void setInputsToJsonService(IDCInputsToJson *newJsonModelBuilderService)
    {
        _jsonModelBuilderService = newJsonModelBuilderService;
    }
    ICreateJsonFromDCPlayer *createJsonFromPlayer() const
    {
        return _createJsonFromPlayer;
    }
    void setCreateJsonFromPlayer(ICreateJsonFromDCPlayer *newCreateJsonFromPlayer)
    {
        _createJsonFromPlayer = newCreateJsonFromPlayer;
    }
    IDCTurnValuesToJson *turnValuesToJson() const
    {
        return _turnValuesToJson;
    }
    void setTurnValuesToJsonService(IDCTurnValuesToJson *newTurnValuesToJson)
    {
        _turnValuesToJson = newTurnValuesToJson;
    }
    IDCIndexesToJson *indexesToJson() const
    {
        return _indexesToJson;
    }
    void setIndexesToJsonService(IDCIndexesToJson *newIndexesToJson)
    {
        _indexesToJson = newIndexesToJson;
    }

    IAddTotalScoreToDartsInputsJson *addTotalScoresToJson() const
    {
        return _addTotalScoresToJson;
    }
    void setAddTotalScoresToJson(IAddTotalScoreToDartsInputsJson *newAddTotalScoresToJson)
    {
        _addTotalScoresToJson = newAddTotalScoresToJson;
    }

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
private:
    IDCInputsToJson *_jsonModelBuilderService;
    ICreateJsonFromDCPlayer *_createJsonFromPlayer;
    IDCTurnValuesToJson *_turnValuesToJson;
    IDCIndexesToJson *_indexesToJson;
    IAddTotalScoreToDartsInputsJson *_addTotalScoresToJson;
    IAddPlayerNamesToJson *_addPlayerNamesToJson;
    IDCJsonResponseBuilder *_responseBuilder;
    IJsonValuesExtractor *_jsonExtractor;
};
#endif // DSJSONSERVICES_H
