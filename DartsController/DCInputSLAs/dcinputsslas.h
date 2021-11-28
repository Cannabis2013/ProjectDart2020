#ifndef DCINPUTSSLAS_H
#define DCINPUTSSLAS_H
#include "DartsController/DCFinishesSLAs/idcfinishbuilder.h"
#include "DartsController/DCInputSLAs/abstractdcinputevaluator.h"
#include "DartsController/DCInputSLAs/abstractdcinputbuilder.h"
#include "idciptconverter.h"
class DCInputsSLAs
{
public:
    AbstractDCInputEvaluator *inputEval() const
    {
        return _inputEvaluator;
    }
    void setInputEvaluator(AbstractDCInputEvaluator *evaluator)
    {
        _inputEvaluator = evaluator;
    }
    IDCFinishBuilder *finishBuilder() const
    {
        return _suggestFinishes;
    }
    void setFinishBuilder(IDCFinishBuilder *service)
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
    IDCIptConverter *iptConverter() const
    {
        return _iptConverter;
    }
    void setIptConverter(IDCIptConverter *newIptConverter)
    {
        _iptConverter = newIptConverter;
    }
private:
    IDCFinishBuilder *_suggestFinishes = nullptr;
    AbstractDCInputEvaluator *_inputEvaluator = nullptr;
    AbstractDCInputBuilder* _inputModelBuilder;
    IDCIptConverter *_iptConverter;
};
#endif // DCINPUTSSLAS_H
