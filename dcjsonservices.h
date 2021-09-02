#ifndef DCJSONSERVICES_H
#define DCJSONSERVICES_H

#include <idcturnvaluestojson.h>
#include <idcmodeltojson.h>
#include <igenericjsonbuilder.h>
#include <ijsontodcinputmodel.h>
#include <iaddtotalscoretodartsinputsjson.h>
#include "icreatejsonfromdcplayer.h"
#include "idcindexestojson.h"

class IAddPlayerNamesToJson;
class DCJsonServices
{
public:
    IDCModelToJson *createJsonFromDSModels() const
    {
        return _jsonModelBuilderService;
    }
    void setJsonModelBuilderService(IDCModelToJson *newJsonModelBuilderService)
    {
        _jsonModelBuilderService = newJsonModelBuilderService;
    }
    IGenericJsonBuilder *jsonGenericBuilder() const
    {
        return _jsonGenericBuilder;
    }
    void setJsonGenericBuilder(IGenericJsonBuilder *newJsonBuilderService)
    {
        _jsonGenericBuilder = newJsonBuilderService;
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
    void setTurnValuesToJson(IDCTurnValuesToJson *newTurnValuesToJson)
    {
        _turnValuesToJson = newTurnValuesToJson;
    }
    IJsonToDCInputModel *jsonToInputModel() const
    {
        return _jsonToInputModel;
    }
    void setJsonToInputModel(IJsonToDCInputModel *newJsonToInputModel)
    {
        _jsonToInputModel = newJsonToInputModel;
    }
    IDCIndexesToJson *indexesToJson() const
    {
        return _indexesToJson;
    }
    void setIndexesToJson(IDCIndexesToJson *newIndexesToJson)
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

private:
    IDCModelToJson *_jsonModelBuilderService;
    IGenericJsonBuilder *_jsonGenericBuilder;
    ICreateJsonFromDCPlayer *_createJsonFromPlayer;
    IDCTurnValuesToJson *_turnValuesToJson;
    IJsonToDCInputModel *_jsonToInputModel;
    IDCIndexesToJson *_indexesToJson;
    IAddTotalScoreToDartsInputsJson *_addTotalScoresToJson;
    IAddPlayerNamesToJson *_addPlayerNamesToJson;
};
#endif // DSJSONSERVICES_H
