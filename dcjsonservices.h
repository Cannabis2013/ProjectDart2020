#ifndef DCJSONSERVICES_H
#define DCJSONSERVICES_H
#include <idcturnvaluestojson.h>
#include <idcinputstojson.h>
#include <iaddtotalscoretodartsinputsjson.h>
#include <iaddplayernamestojson.h>
#include <ijsonkeyplayer.h>
#include "icreatejsonfromdcplayer.h"
#include "idccreatejsonresponse.h"
#include "DCIndexSLA/idcindexestojson.h"
#include "ijsonvaluesextractor.h"
class IAddPlayerNamesToJson;
class DCJsonServices
{
public:
    IDCTurnValuesToJson *turnValuesToJson() const
    {
        return _turnValuesToJson;
    }
    void setTurnValuesToJsonService(IDCTurnValuesToJson *newTurnValuesToJson)
    {
        _turnValuesToJson = newTurnValuesToJson;
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


    IAddPlayerNamesToJson *_addPlayerNamesToJson;
    IDCTurnValuesToJson *_turnValuesToJson;
    IJsonValuesExtractor *_jsonExtractor;
    IDCJsonResponseBuilder *_responseBuilder;
};
#endif // DSJSONSERVICES_H
