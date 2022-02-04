#include "jsontoinput.h"

#include "Inputs/Models/input.h"
#include "qjsonobject.h"

JsonToInput::Input JsonToInput::convert(const Json &json) const
{
    Input ipt;
    ipt.name = json.value("inputPlayerName").toString();
    ipt.point = json.value("point").toInt();
    ipt.score = json.value("score").toInt();
    ipt.keyCode = json.value("modKeyCode").toInt();
    return ipt;
}
