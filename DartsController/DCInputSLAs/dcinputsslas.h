#ifndef DCINPUTSSLAS_H
#define DCINPUTSSLAS_H
#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"
#include "DartsController/DCInputSLAs/abstractdcinputevaluator.h"
#include "DartsController/DCInputSLAs/idcinputbuilder.h"
class DCInputsSLAs
{
public:
    AbstractDCInputEvaluator *evaluateInput() const
    {
        return _inputEvaluator;
    }
    void setInputEvaluator(AbstractDCInputEvaluator *evaluator)
    {
        _inputEvaluator = evaluator;
    }
    IDartsInputFinishes *dartsFinishBuilder() const
    {
        return _suggestFinishes;
    }
    void setSuggestFinishes(IDartsInputFinishes *service)
    {
        _suggestFinishes = service;
    }
    IDCInputBuilder *createInput() const
    {
        return _inputModelBuilder;
    }
    void setInputBuilder(IDCInputBuilder *service)
    {
        _inputModelBuilder = service;
    }
private:
    IDartsInputFinishes *_suggestFinishes = nullptr;
    AbstractDCInputEvaluator *_inputEvaluator = nullptr;
    IDCInputBuilder* _inputModelBuilder;
};
#endif // DCINPUTSSLAS_H
