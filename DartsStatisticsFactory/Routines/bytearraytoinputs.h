#ifndef BYTEARRAYTOINPUTS_H
#define BYTEARRAYTOINPUTS_H
#include "Routines/IJsonToModels.h"
template<typename T> class IJsonToInput;
class Input;
class JsonToInput;
class ServicesContext;
class ByteArrayToInputs : public IJsonToModels<Input>
{
public:
    typedef IJsonToInput<Input> JsonToInput;
    ByteArrayToInputs(ServicesContext *provider);
    virtual Models convert(const ByteArray &ba) const override;
private:
    ServicesContext *_provider;
    JsonToInput *_jsonToInput;
};

#endif // BYTEARRAYTOINPUTS_H
