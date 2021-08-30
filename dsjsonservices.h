#ifndef DSJSONSERVICES_H
#define DSJSONSERVICES_H

#include <ibytearrayjsonmerger.h>
#include <idscindexes.h>
#include <idscmodel.h>
#include <idsjsonbuilder.h>
#include <igenericjsonbuilder.h>
#include <imhjsonextractor.h>
#include "icreatejsonfromdcplayer.h"

class DSJsonServices
{
public:
    IDSJsonBuilder *createJsonFromDSModels() const
    {
        return _jsonModelBuilderService;
    }
    void setJsonModelBuilderService(IDSJsonBuilder *newJsonModelBuilderService)
    {
        _jsonModelBuilderService = newJsonModelBuilderService;
    }
    IByteArrayJsonMerger *jsonMerger() const
    {
        return _jsonMergeService;
    }
    void setJsonMerger(IByteArrayJsonMerger *newJsonMergeService)
    {
        _jsonMergeService = newJsonMergeService;
    }
    IGenericJsonBuilder *jsonBuilder() const
    {
        return _jsonBuilderService;
    }
    void setJsonBuilderService(IGenericJsonBuilder *newJsonBuilderService)
    {
        _jsonBuilderService = newJsonBuilderService;
    }
    IMHJsonExtractor *extractJson() const
    {
        return _extractJsonService;
    }
    void setExtractJsonService(IMHJsonExtractor *newExtractJsonService)
    {
        _extractJsonService = newExtractJsonService;
    }
    ICreateJsonFromDCPlayer *createJsonFromPlayer() const
    {
        return _createJsonFromPlayer;
    }
    void setCreateJsonFromPlayer(ICreateJsonFromDCPlayer *newCreateJsonFromPlayer)
    {
        _createJsonFromPlayer = newCreateJsonFromPlayer;
    }
private:
    IDSJsonBuilder *_jsonModelBuilderService;
    IByteArrayJsonMerger* _jsonMergeService;
    IGenericJsonBuilder *_jsonBuilderService;
    IMHJsonExtractor *_extractJsonService;
    ICreateJsonFromDCPlayer *_createJsonFromPlayer;

};
#endif // DSJSONSERVICES_H
