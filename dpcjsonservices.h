#ifndef DPCJSONSERVICES_H
#define DPCJSONSERVICES_H

#include <iaddplayernamestojson.h>
#include <iaddtotalscoretodartsinputsjson.h>
#include <idccreatejsonresponse.h>
#include <icreatejsonfromdcplayer.h>
#include <icreatejsonfromdcpoint.h>
#include <idartsinputstojson.h>
#include <igenericjsonbuilder.h>
#include <imhjsonextractor.h>

class DPCJsonServices
{
public:
    typedef IDartsInputsToJson<DCContext::IDCModel,QByteArray> DartsInputsToJsonService;
    IGenericJsonBuilder *jsonBuilder() const
    {
        return _jsonBuilder;
    }
    void setJsonBuilder(IGenericJsonBuilder *newJsonBuilder)
    {
        _jsonBuilder = newJsonBuilder;
    }
    IMHJsonExtractor *jsonExtractor() const
    {
        return _jsonExtractor;
    }
    void setJsonExtractor(IMHJsonExtractor *newJsonExtractor)
    {
        _jsonExtractor = newJsonExtractor;
    }
    DPCContext::IAddTotalScoreToDartsInputsJson *addTotalScoresToDartsModelsJson() const
    {
        return _addTotalScoresToDartsModelsJson;
    }
    void setAddTotalScoresToDartsModelsJson(DPCContext::IAddTotalScoreToDartsInputsJson *newAddTotalScoresToDartsModelsJson)
    {
        _addTotalScoresToDartsModelsJson = newAddTotalScoresToDartsModelsJson;
    }
    DartsInputsToJsonService *dartsPointsToJson() const
    {
        return _dartsPointsToJson;
    }
    void setDartsPointsToJson(DartsInputsToJsonService *newDartsPointsToJson)
    {
        _dartsPointsToJson = newDartsPointsToJson;
    }
    IDCCreateJsonResponse *jsonMerger() const
    {
        return _jsonMerger;
    }
    void setJsonMerger(IDCCreateJsonResponse *newJsonMerger)
    {
        _jsonMerger = newJsonMerger;
    }
    IAddPlayerNamesToJson *addPlayerNamesToDartsModelsJson() const
    {
        return _addPlayerNamesToDartsModelsJson;
    }
    void setAddPlayerNamesToDartsModelsJson(IAddPlayerNamesToJson *newAddPlayerNamesToDartsModelsJson)
    {
        _addPlayerNamesToDartsModelsJson = newAddPlayerNamesToDartsModelsJson;
    }
    ICreateJsonFromDCPlayer *createJsonFromPlayer() const
    {
        return _createJsonFromPlayer;
    }
    void setCreateJsonFromPlayer(ICreateJsonFromDCPlayer *newCreateJsonFromPlayer)
    {
        _createJsonFromPlayer = newCreateJsonFromPlayer;
    }
    ICreateJsonFromDCPoint *createJsonFromPoint() const
    {
        return _createJsonFromPoint;
    }
    void setCreateJsonFromPoint(ICreateJsonFromDCPoint *newCreateJsonFromPoint)
    {
        _createJsonFromPoint = newCreateJsonFromPoint;
    }
private:
    IGenericJsonBuilder *_jsonBuilder;
    IMHJsonExtractor *_jsonExtractor;
    DPCContext::IAddTotalScoreToDartsInputsJson *_addTotalScoresToDartsModelsJson;
    DartsInputsToJsonService * _dartsPointsToJson;
    IDCCreateJsonResponse *_jsonMerger;
    IAddPlayerNamesToJson *_addPlayerNamesToDartsModelsJson;
    ICreateJsonFromDCPlayer *_createJsonFromPlayer;
    ICreateJsonFromDCPoint *_createJsonFromPoint;
};
#endif // DPCJSONSERVICES_H
