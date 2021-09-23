#ifndef IDARTSINPUTFINISHES_H
#define IDARTSINPUTFINISHES_H

#include <qstring.h>

class IDartsInputFinishes
{
public:
    virtual QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const = 0;
};

#endif // ILOGISTICMANAGER_H
