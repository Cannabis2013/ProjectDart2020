#ifndef DCINPUTSSLAS_H
#define DCINPUTSSLAS_H
#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"
#include "DartsController/DCInputSLAs/abstractdcinputevaluator.h"
#include "DartsController/DCInputSLAs/abstractdcinputbuilder.h"
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
    void setDartsFinishBuilder(IDartsInputFinishes *service)
    {
        _suggestFinishes = service;
    }
    AbstractDCInputBuilder *createInput() const
    {
        return _inputModelBuilder;
    }
    void setInputBuilder(AbstractDCInputBuilder *service)
    {
        _inputModelBuilder = service;
    }
private:
    IDartsInputFinishes *_suggestFinishes = nullptr;
    AbstractDCInputEvaluator *_inputEvaluator = nullptr;
    AbstractDCInputBuilder* _inputModelBuilder;
};
#endif // DCINPUTSSLAS_H
