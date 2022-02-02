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
    JsonToInput *jsonToInput() const {return _jsonToInput;}
    void setJsonToInput(JsonToInput *service) {_jsonToInput = service;}
    InputsDb *inputsDb() const {return _inputsDb;}
    void setInputsDb(InputsDb *service) {_inputsDb = service;}
    ICreateInput *createInput() const {return _createInput;}
    void setCreateInput(ICreateInput *newCreateInput) {_createInput = newCreateInput;}
private:
    JsonToInput *_jsonToInput;
    InputsDb *_inputsDb;
    ICreateInput *_createInput;
};
#endif // INPUTSERVICES_H
