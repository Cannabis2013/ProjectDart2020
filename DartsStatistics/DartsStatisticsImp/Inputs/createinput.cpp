#include "createinput.h"

#include <DartsStatistics/Contracts/Inputs/Models/snapshot.h>

CreateInput::Ipt CreateInput::create(const QString &name, const int &score, const int &modCode) const
{
        Ipt SnapShot;
        SnapShot.name = name;
        SnapShot.score = score;
        SnapShot.keyCode = modCode;
        return SnapShot;
}
