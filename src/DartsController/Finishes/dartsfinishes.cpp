#include "dartsfinishes.h"

DartsFinishes::DartsFinishes()
{
        _finishes = _constructRow->constructRows();
}

QString DartsFinishes::suggestTargetRow(const int &remainingScore, const int &turnIndex) const
{
    if(turnIndex < 0 || turnIndex > 2)
        return QString();
    else if(remainingScore > 170)
        return QString();
    return getTargetRow(turnIndex,remainingScore);
}

QString DartsFinishes::getTargetRow(const int &turnIndex, const int &remainingScore) const
{
    try {
        auto row = _finishes->at(turnIndex);
        auto valuesAtKey = row->values(remainingScore);
        auto count = valuesAtKey.count();
        if (count == 0)
                return QString();
        return valuesAtKey.at(0);
    } catch (...) {
        return QString();
    }
}
