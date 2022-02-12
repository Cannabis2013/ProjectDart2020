#ifndef DCINPUTSSLAS_H
#define DCINPUTSSLAS_H
#include "DCInputSLAs/idcinputevaluator.h"
#include "DCInputSLAs/idcinputadder.h"
#include "idcexternaliptservice.h"
#include "idcinputbuilder.h"
#include "DCInputSLAs/idcaddtomdsctx.h"
#include "ModelsConverterSLAs/idcmodelsconverter.h"
#include "DCInputSLAs/idcbytearraytoinput.h"
class DCInputsSLAs
{
public:
    typedef DCInput Input;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IDCInputBuilder<Input> InputBuilder;
    IDCInputEvaluator *evaluateInput() const {return _iptEval;}
    void setInputEvaluator(IDCInputEvaluator *service) {_iptEval = service;}
    IDCInputAdder *AddInputDetails() const {return _inputAdder;}
    void setInputAdder(IDCInputAdder *service) {_inputAdder = service;}
    InputBuilder *iptBuilder() const {return _inputConverter;}
    void setInputConverter(InputBuilder *service) {_inputConverter = service;}
    IDCModelsConverter<DCInput> *convertInputs() const {return _convertInputs;}
    void setConvertInputs(IDCModelsConverter<DCInput> *service) {_convertInputs = service;}
    IDCByteArrayToInput *createInputModel() const {return _assembleInput;}
    void setAssembleInput(IDCByteArrayToInput *service) {_assembleInput = service;}
    IDCExternalIptService *externalInputService() const {return _getInputFromMdsService;}
    void setGetInputFromMdsService(IDCExternalIptService *newGetInputFromMdsService) {_getInputFromMdsService = newGetInputFromMdsService;}
private:
    IDCInputEvaluator *_iptEval = nullptr;
    IDCInputAdder* _inputAdder;
    InputBuilder *_inputConverter;
    IDCModelsConverter<DCInput> *_convertInputs;
    IDCByteArrayToInput *_assembleInput;
    IDCExternalIptService *_getInputFromMdsService;
};
#endif // DCINPUTSSLAS_H
