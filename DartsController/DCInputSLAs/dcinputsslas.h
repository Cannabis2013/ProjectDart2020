#ifndef DCINPUTSSLAS_H
#define DCINPUTSSLAS_H
#include "DartsController/DCFinishesSLAs/idcfinishbuilder.h"
#include "DartsController/DCInputSLAs/idcipteval.h"
#include "DartsController/DCInputSLAs/abstractdcinputbuilder.h"
#include "abstractdciptconverter.h"
#include "DartsController/ModelsComCtxSLAs/abstractdcaddtomdsctx.h"
class DCInputsSLAs
{
public:
    IDCIptEval *evalIpt() const {return _iptEval;}
    void setInputEvaluator(IDCIptEval *evaluator) {_iptEval = evaluator;}
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
    IDCIptEval *_iptEval = nullptr;
    AbstractDCInputBuilder* _inputModelBuilder;
    AbstractDCIptConverter *_iptConverter;
    AbstractDCAddToMdsCtx *_addToModelsCtx;
};
#endif // DCINPUTSSLAS_H
