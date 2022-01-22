#ifndef DCINPUTSSLAS_H
#define DCINPUTSSLAS_H
#include "DCInputSLAs/idcipteval.h"
#include "DCInputSLAs/idcinputadder.h"
#include "idcinputbuilder.h"
#include "ModelsComCtxSLAs/idcaddtomdsctx.h"
#include "ModelsConverterSLAs/idcmodelsconverter.h"
class DCInputsSLAs
{
public:
    typedef DCInput Input;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IDCInputBuilder<Input,ByteArray,Json> InputBuilder;
    IDCIptEval *evalIpt() const {return _iptEval;}
    void setInputEvaluator(IDCIptEval *service) {_iptEval = service;}
    IDCInputAdder *AddInputDetails() const {return _inputModelBuilder;}
    void setCreateInput(IDCInputAdder *service) {_inputModelBuilder = service;}
    IDCAddToMdsCtx *addToModelsCtx() const {return _addToModelsCtx;}
    void setAddToModelsCtx(IDCAddToMdsCtx *service) {_addToModelsCtx = service;}
    InputBuilder *inputBuilder() const {return _inputConverter;}
    void setInputConverter(InputBuilder *service) {_inputConverter = service;}
    IDCModelsConverter<DCInput, QJsonObject> *convertInputs() const {return _convertInputs;}
    void setConvertInputs(IDCModelsConverter<DCInput, QJsonObject> *service) {_convertInputs = service;}
private:
    IDCIptEval *_iptEval = nullptr;
    IDCInputAdder* _inputModelBuilder;
    IDCAddToMdsCtx *_addToModelsCtx;
    InputBuilder *_inputConverter;
    IDCModelsConverter<DCInput,QJsonObject> *_convertInputs;
};
#endif // DCINPUTSSLAS_H
