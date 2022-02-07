#include "createinput.h"

#include "Inputs/Models/input.h"

CreateInput::Ipt CreateInput::create(const QString &name, const int &score, const int &modCode) const
{
    Ipt ipt;
    ipt.name = name;
    ipt.score = score;
    ipt.keyCode = modCode;
    return ipt;
}
