#ifndef DCINPUTSSLAS_H
#define DCINPUTSSLAS_H
#include "DartsController/DCFinishesSLAs/idcfinishbuilder.h"
#include "DartsController/DCInputSLAs/abstractdcinputevaluator.h"
#include "DartsController/DCInputSLAs/abstractdcinputbuilder.h"
#include "abstractdciptconverter.h"
class DCInputsSLAs
{
public:
    AbstractDCInputEvaluator *evaluateIpt() const {return _inputEvaluator;}
    void setInputEvaluator(AbstractDCInputEvaluator *evaluator) {_inputEvaluator = evaluator;}
    IDCFinishBuilder *finishBuilder() const {return _suggestFinishes;}
    void setFinishBuilder(IDCFinishBuilder *service) {_suggestFinishes = service;}
    AbstractDCInputBuilder *createInput() const {return _inputModelBuilder;}
    void setCreateInput(AbstractDCInputBuilder *service) {_inputModelBuilder = service;}
    AbstractDCIptConverter *iptConverter() const {return _iptConverter;}
    void setIptConverter(AbstractDCIptConverter *newIptConverter) {_iptConverter = newIptConverter;}
    AbstractDCAddToMdsCtx *addToModelsCtx() const {return _addToModelsCtx;}
    void setAddToModelsCtx(AbstractDCAddToMdsCtx *newAddToModelsCtx) {_addToModelsCtx = newAddToModelsCtx;}
private:
    IDCFinishBuilder *_suggestFinishes = nullptr;
    AbstractDCInputEvaluator *_inputEvaluator = nullptr;
    AbstractDCInputBuilder* _inputModelBuilder;
    AbstractDCIptConverter *_iptConverter;
    AbstractDCAddToMdsCtx *_addToModelsCtx;
};
#endif // DCINPUTSSLAS_H
