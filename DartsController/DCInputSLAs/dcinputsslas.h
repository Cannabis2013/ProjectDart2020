#ifndef DCINPUTSSLAS_H
#define DCINPUTSSLAS_H

#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"
#include "DartsController/DCInputSLAs/abstractevaluatedcinput.h"
#include "DartsController/DCInputSLAs/idcinputbuilder.h"
#include "DartsController/DCInputSLAs/idcsetinputjsonvalues.h"
#include "DartsController/DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
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
    IDCInputBuilder *inputBuilder() const
    {
        return _inputModelBuilder;
    }
    void setInputBuilder(IDCInputBuilder *service)
    {
        _inputModelBuilder = service;
    }
    IDCSetInputJsonValues *setJsonInputValues() const
    {
        return _jsonModelBuilderService;
    }
    void setInputJsonContext(IDCSetInputJsonValues *service)
    {
        _jsonModelBuilderService = service;
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
    IDCInputBuilder* _inputModelBuilder;
    IDCSetInputJsonValues *_jsonModelBuilderService;
    IDCInputKeyCodes *_inputKeyCodes;
};
#endif // DCINPUTSSLAS_H
