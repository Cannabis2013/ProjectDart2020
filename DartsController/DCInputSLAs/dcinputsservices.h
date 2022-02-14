#ifndef DCINPUTSSERVICES_H
#define DCINPUTSSERVICES_H
#include "DCInputSLAs/idcinputadder.h"
#include "idcinputbuilder.h"
#include "idcinputevaluator.h"
#include "ModelsConverterSLAs/idcjsontomodels.h"
class DCInputsServices
{
public:
    typedef DCInput Input;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IDCInputBuilder<Input> InputBuilder;
    typedef IDCJsonToModels<DCInput> ByteArrayToInputs;
    IDCInputAdder *AddInputDetails() const {return _inputAdder;}
    void setInputAdder(IDCInputAdder *service) {_inputAdder = service;}
    InputBuilder *createInput() const {return _inputConverter;}
    void setInputConverter(InputBuilder *service) {_inputConverter = service;}
    ByteArrayToInputs *jsonToInputModels() const {return _jsonToInputModels;}
    void setJsonToInputModels(ByteArrayToInputs *service) {_jsonToInputModels = service;}
    IDCInputEvaluator *evaluateInput() const {return _iptEval;}
    void setInputEvaluator(IDCInputEvaluator *service) {_iptEval = service;}
private:
    IDCInputEvaluator *_iptEval;
    IDCInputAdder* _inputAdder;
    InputBuilder *_inputConverter;
    ByteArrayToInputs *_jsonToInputModels;
};
#endif // DCINPUTSSERVICES_H
