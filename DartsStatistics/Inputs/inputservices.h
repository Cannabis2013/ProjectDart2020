#ifndef INPUTSERVICES_H
#define INPUTSERVICES_H
#include "icreateinput.h"
#include "ijsontoinput.h"
#include "Models/input.h"
#include "Db/istatsdb.h"
class InputServices
{
public:
    typedef IJsonToInput<Input> JsonToInput;
    typedef IStatsDb<Input> InputsDb;
    typedef ICreateInput<Input> CreateInput;
    JsonToInput *jsonToInput() const {return _jsonToInput;}
    void setJsonToInput(JsonToInput *service) {_jsonToInput = service;}
    InputsDb *inputsDb() const {return _inputsDb;}
    void setInputsDb(InputsDb *service) {_inputsDb = service;}
    CreateInput *createInput() const {return _createInput;}
    void setCreateInput(CreateInput *newCreateInput) {_createInput = newCreateInput;}
private:
    JsonToInput *_jsonToInput;
    InputsDb *_inputsDb;
    CreateInput *_createInput;
};
#endif // INPUTSERVICES_H
