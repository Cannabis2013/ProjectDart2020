#ifndef INPUTSERVICES_H
#define INPUTSERVICES_H
#include "ijsontoinput.h"
#include "input.h"
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
private:
    JsonToInput *_jsonToInput;
    InputsDb *_inputsDb;
};
#endif // INPUTSERVICES_H
