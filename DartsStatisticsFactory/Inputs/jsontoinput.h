#ifndef JSONTOINPUT_H
#define JSONTOINPUT_H
#include "Inputs/ijsontoinput.h"
struct Input;
class JsonToInput : public IJsonToInput<Input>
{
public:
    virtual Input convert(const Json &json) const override;
};

#endif // JSONTOINPUT_H
