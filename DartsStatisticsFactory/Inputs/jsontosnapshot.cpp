#include "jsontosnapshot.h"
#include "Inputs/Models/snapshot.h"
#include "qjsonobject.h"

SnapShot JsonToSnapShot::convert(const Json &json) const
{
    SnapShot ipt;
    ipt.name = json.value("inputPlayerName").toString();
    ipt.score = json.value("score").toInt();
    ipt.keyCode = json.value("modKeyCode").toInt();
    return ipt;
}
