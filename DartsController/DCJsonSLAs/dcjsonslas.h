#ifndef DCJSONSLAS_H
#define DCJSONSLAS_H
#include "DartsController/DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
#include "DartsController/DCJsonSLAs/iaddplayernamestojson.h"
#include "IDCJsonBuilder.h"

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
    IDCJsonBuilder *jsonBuilder() const
    {
        return _jsonResponseBuilder;
    }
    void setJsonResponseBuilder(IDCJsonBuilder *newJsonResponseBuilder)
    {
        _jsonResponseBuilder = newJsonResponseBuilder;
    }
private:
    IDCJsonBuilder *_jsonResponseBuilder;
    IAddPlayerNamesToJson *_addPlayerNamesToJson;
    IAddTotalScoreToDartsInputsJson *_addTotalScoresToJson;
};
#endif // DSJSONSERVICES_H
