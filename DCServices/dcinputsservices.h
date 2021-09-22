#ifndef DCINPUTSSERVICES_H
#define DCINPUTSSERVICES_H

#include "DCInputsSLA/idartsinputfinishes.h"
#include "DCInputsSLA/idartsinputvalidator.h"
#include "idccreateinputmodel.h"
#include "idcinputstojson.h"
#include "iaddtotalscoretodartsinputsjson.h"
#include "DCInputsSLA/idcreateinputmodels.h"
class DCInputsServices
{
public:
    IDartsInputValidator *inputEvaluator() const
    {
        return _inputEvaluator;
    }
    void setInputEvaluator(IDartsInputValidator *service)
    {
        _inputEvaluator = service;
    }
    IDartsInputFinishes *suggestFinishes() const
    {
        return _suggestFinishes;
    }
    void setSuggestFinishes(IDartsInputFinishes *service)
    {
        _suggestFinishes = service;
    }
    IDCCreateInputModel *createInputModel() const
    {
        return _inputModelBuilder;
    }
    void setCreateInputModelService(IDCCreateInputModel *newDartsScoreBuilder)
    {
        _inputModelBuilder = newDartsScoreBuilder;
    }
    IDCInputsToJson *inputsToJson() const
    {
        return _jsonModelBuilderService;
    }
    void setInputsToJsonService(IDCInputsToJson *newJsonModelBuilderService)
    {
        _jsonModelBuilderService = newJsonModelBuilderService;
    }
    IAddTotalScoreToDartsInputsJson *addTotalScoresToJson() const
    {
        return _addTotalScoresToJson;
    }
    void setAddTotalScoresToJson(IAddTotalScoreToDartsInputsJson *newAddTotalScoresToJson)
    {
        _addTotalScoresToJson = newAddTotalScoresToJson;
    }
    IDCCreateInputModels *createInputModels() const
    {
        return _createInputModels;
    }
    void setCreateInputModels(IDCCreateInputModels *newCreateInputModels)
    {
        _createInputModels = newCreateInputModels;
    }
private:
    IDartsInputFinishes *_suggestFinishes = nullptr;
    IDartsInputValidator* _inputEvaluator = nullptr;
    IDCCreateInputModel* _inputModelBuilder;
    IDCInputsToJson *_jsonModelBuilderService;
    IAddTotalScoreToDartsInputsJson *_addTotalScoresToJson;
    IDCCreateInputModels *_createInputModels;
};
#endif // DCINPUTSSERVICES_H
