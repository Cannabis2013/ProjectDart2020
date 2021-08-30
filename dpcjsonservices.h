#ifndef DPCJSONSERVICES_H
#define DPCJSONSERVICES_H

#include <iaddplayernamestojsonentity.h>
#include <iaddtotalscoretodartsinputsjson.h>
#include <ibytearrayjsonmerger.h>
#include <icreatejsonfromdcplayer.h>
#include <icreatejsonfromdpcpoint.h>
#include <idartsinputstojson.h>
#include <igenericjsonbuilder.h>
#include <imhjsonextractor.h>

class DPCJsonServices
{
public:
    typedef IDartsInputsToJson<DPCContext::IDPCModel,QByteArray> DartsInputsToJsonService;
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
    IByteArrayJsonMerger *jsonMerger() const
    {
        return _jsonMerger;
    }
    void setJsonMerger(IByteArrayJsonMerger *newJsonMerger)
    {
        _jsonMerger = newJsonMerger;
    }
    IAddPlayerNamesToJsonEntity *addPlayerNamesToDartsModelsJson() const
    {
        return _addPlayerNamesToDartsModelsJson;
    }
    void setAddPlayerNamesToDartsModelsJson(IAddPlayerNamesToJsonEntity *newAddPlayerNamesToDartsModelsJson)
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
    ICreateJsonFromDPCPoint *createJsonFromPoint() const
    {
        return _createJsonFromPoint;
    }
    void setCreateJsonFromPoint(ICreateJsonFromDPCPoint *newCreateJsonFromPoint)
    {
        _createJsonFromPoint = newCreateJsonFromPoint;
    }
private:
    IGenericJsonBuilder *_jsonBuilder;
    IMHJsonExtractor *_jsonExtractor;
    DPCContext::IAddTotalScoreToDartsInputsJson *_addTotalScoresToDartsModelsJson;
    DartsInputsToJsonService * _dartsPointsToJson;
    IByteArrayJsonMerger *_jsonMerger;
    IAddPlayerNamesToJsonEntity *_addPlayerNamesToDartsModelsJson;
    ICreateJsonFromDCPlayer *_createJsonFromPlayer;
    ICreateJsonFromDPCPoint *_createJsonFromPoint;
};
#endif // DPCJSONSERVICES_H
