#ifndef DCINPUTSSERVICES_H
#define DCINPUTSSERVICES_H

#include "DCFinishesSLAs/idartsinputfinishes.h"
#include "DCInputSLAs/idartsinputvalidator.h"
#include "DCInputSLAs/idccreateinputmodel.h"
#include "DCInputSLAs/idcinputstojson.h"
#include "DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
#include "DCInputSLAs/idccreateinputmodels.h"
#include "DCInputSLAs/idcinputjsonkeys.h"
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
    IDCCreateInputModels *createInputModels() const
    {
        return _createInputModels;
    }
    void setCreateInputModels(IDCCreateInputModels *newCreateInputModels)
    {
        _createInputModels = newCreateInputModels;
    }
    IDCInputJsonKeys *inputKeys() const
    {
        return _inputKeys;
    }
    void setInputKeys(IDCInputJsonKeys *newInputKeys)
    {
        _inputKeys = newInputKeys;
    }
private:
    IDartsInputFinishes *_suggestFinishes = nullptr;
    IDartsInputValidator* _inputEvaluator = nullptr;
    IDCCreateInputModel* _inputModelBuilder;
    IDCInputsToJson *_jsonModelBuilderService;
    IDCCreateInputModels *_createInputModels;
    IDCInputJsonKeys *_inputKeys;
};
#endif // DCINPUTSSERVICES_H
