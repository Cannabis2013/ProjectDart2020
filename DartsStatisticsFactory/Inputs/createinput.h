#ifndef CREATEINPUT_H
#define CREATEINPUT_H
#include "Inputs/icreateinput.h"
struct Input;
class CreateInput : public ICreateInput<Input>
{
public:
    virtual Ipt create(const QString &name, const int &point, const int &score, const int &modCode) const override;
};

#endif // CREATEINPUT_H
