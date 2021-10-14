#ifndef DCINPUTSSLAS_H
#define DCINPUTSSLAS_H

#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"
#include "DartsController/DCInputSLAs/abstractevaluatedcinput.h"
#include "DartsController/DCInputSLAs/idccreateinputmodel.h"
#include "DartsController/DCInputSLAs/idcinputjsoncontext.h"
#include "DartsController/DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
#include "DartsController/DCInputSLAs/idccreateinputmodels.h"
#include "DartsController/DCInputSLAs/idcinputjsonkeys.h"
#include "IDCInputKeyCodes.h"

class DCInputsSLAs
{
public:
    AbstractEvaluateDCInput *inputEvaluator() const
    {
        return _inputEvaluator;
    }
    void setInputEvaluator(AbstractEvaluateDCInput *service)
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
    void setCreateInputModelService(IDCCreateInputModel *service)
    {
        _inputModelBuilder = service;
    }
    IDCInputJsonContext *inputJsonContext() const
    {
        return _jsonModelBuilderService;
    }
    void setInputJsonContext(IDCInputJsonContext *service)
    {
        _jsonModelBuilderService = service;
    }
    IDCCreateInputModels *createInputModels() const
    {
        return _createInputModels;
    }
    void setCreateInputModels(IDCCreateInputModels *service)
    {
        _createInputModels = service;
    }
    IDCInputJsonKeys *inputKeys() const
    {
        return _inputKeys;
    }
    void setInputKeys(IDCInputJsonKeys *service)
    {
        _inputKeys = service;
    }
    IDCInputKeyCodes *inputKeyCodes() const
    {
        return _inputKeyCodes;
    }
    void setInputKeyCodes(IDCInputKeyCodes *service)
    {
        _inputKeyCodes = service;
    }
private:
    IDartsInputFinishes *_suggestFinishes = nullptr;
    AbstractEvaluateDCInput *_inputEvaluator = nullptr;
    IDCCreateInputModel* _inputModelBuilder;
    IDCInputJsonContext *_jsonModelBuilderService;
    IDCCreateInputModels *_createInputModels;
    IDCInputJsonKeys *_inputKeys;
    IDCInputKeyCodes *_inputKeyCodes;
};
#endif // DCINPUTSSLAS_H
