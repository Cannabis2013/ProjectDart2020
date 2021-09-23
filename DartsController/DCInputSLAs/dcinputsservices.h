#ifndef DCINPUTSSERVICES_H
#define DCINPUTSSERVICES_H

#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"
#include "DartsController/DCInputSLAs/idartsinputvalidator.h"
#include "DartsController/DCInputSLAs/idccreateinputmodel.h"
#include "DartsController/DCInputSLAs/idcinputstojson.h"
#include "DartsController/DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
#include "DartsController/DCInputSLAs/idccreateinputmodels.h"
#include "DartsController/DCInputSLAs/idcinputjsonkeys.h"
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
