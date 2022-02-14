#ifndef DCINPUTSSERVICES_H
#define DCINPUTSSERVICES_H
#include "Inputs/idcinputadder.h"
#include "idcinputbuilder.h"
#include "idcinputconverter.h"
#include "idcinputevaluator.h"
#include "Converters/idcjsontomodels.h"
class DCInputsServices
{
public:
    typedef DCInput Input;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IDCInputConverter<Input> InputConverter;
    typedef IDCInputBuilder<Input> InputBuilder;
    typedef IDCJsonToModels<DCInput> ByteArrayToInputs;
    IDCInputAdder *AddInputDetails() const {return _inputAdder;}
    void setInputAdder(IDCInputAdder *service) {_inputAdder = service;}
    InputBuilder *createInputModel() const {return _inputBuilder;}
    void setCreateInputModel(InputBuilder *service) {_inputBuilder = service;}
    ByteArrayToInputs *jsonToInputModels() const {return _jsonToInputModels;}
    void setJsonToInputModels(ByteArrayToInputs *service) {_jsonToInputModels = service;}
    IDCInputEvaluator *evaluateInput() const {return _iptEval;}
    void setInputEvaluator(IDCInputEvaluator *service) {_iptEval = service;}
    InputConverter *inputConverter() const {return _inputConverter;}
    void setInputConverter(InputConverter *service) {_inputConverter = service;}
private:
    IDCInputEvaluator *_iptEval;
    IDCInputAdder* _inputAdder;
    InputBuilder *_inputBuilder;
    InputConverter *_inputConverter;
    ByteArrayToInputs *_jsonToInputModels;
};
#endif // DCINPUTSSERVICES_H
