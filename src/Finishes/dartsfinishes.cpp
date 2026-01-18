#include "dartsfinishes.h"

DartsFinishes::DartsFinishes()
{
    _finishes = _finishConstructor->construct();
}

QString DartsFinishes::finish(const int &remainingScore, const int &turnIndex) const
{
    if(turnIndex < 0 || turnIndex > 2)
        return QString();
    else if(remainingScore > 170)
        return QString();
    return getTargetRow(turnIndex,remainingScore);
}

QString DartsFinishes::getTargetRow(const int &turnIndex, const int &remainingScore) const
{
    auto row = _finishes->at(turnIndex);
    auto valuesAtKey = row->values(remainingScore);
    auto count = valuesAtKey.count();
    return count > 0 ? valuesAtKey.at(0) : QString();
}
