#ifndef DCINPUTSSLAS_H
#define DCINPUTSSLAS_H
#include "DCInputSLAs/idcipteval.h"
#include "DCInputSLAs/idcinputadder.h"
#include "idcgetinput.h"
#include "idcinputbuilder.h"
#include "DCInputSLAs/idcaddtomdsctx.h"
#include "ModelsConverterSLAs/idcmodelsconverter.h"
#include "DCInputSLAs/idcassembleinput.h"
class DCInputsSLAs
{
public:
    typedef DCInput Input;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IDCInputBuilder<Input> InputBuilder;
    IDCIptEval *evalIpt() const {return _iptEval;}
    void setInputEvaluator(IDCIptEval *service) {_iptEval = service;}
    IDCInputAdder *AddInputDetails() const {return _inputAdder;}
    void setInputAdder(IDCInputAdder *service) {_inputAdder = service;}
    InputBuilder *iptBuilder() const {return _inputConverter;}
    void setInputConverter(InputBuilder *service) {_inputConverter = service;}
    IDCModelsConverter<DCInput> *convertInputs() const {return _convertInputs;}
    void setConvertInputs(IDCModelsConverter<DCInput> *service) {_convertInputs = service;}
    IDCAssembleInput *assembleInput() const {return _assembleInput;}
    void setAssembleInput(IDCAssembleInput *service) {_assembleInput = service;}
    IDCGetInput *getInputFromMdsService() const {return _getInputFromMdsService;}
    void setGetInputFromMdsService(IDCGetInput *newGetInputFromMdsService) {_getInputFromMdsService = newGetInputFromMdsService;}
private:
    IDCIptEval *_iptEval = nullptr;
    IDCInputAdder* _inputAdder;
    InputBuilder *_inputConverter;
    IDCModelsConverter<DCInput> *_convertInputs;
    IDCAssembleInput *_assembleInput;
    IDCGetInput *_getInputFromMdsService;
};
#endif // DCINPUTSSLAS_H
