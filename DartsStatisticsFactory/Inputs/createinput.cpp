#include "createinput.h"

#include "Inputs/Models/input.h"

CreateInput::Ipt CreateInput::create(const QString &name, const int &point, const int &score, const int &modCode) const
{
    Ipt ipt;
    ipt.name = name;
    ipt.point = point;
    ipt.score = score;
    ipt.keyCode = modCode;
    return ipt;
}
