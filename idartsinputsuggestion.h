#ifndef IDARTSINPUTSUGGESTION_H
#define IDARTSINPUTSUGGESTION_H

#include <qstring.h>

class IDartsInputSuggestion
{
public:
    virtual QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const = 0;
};

#endif // ILOGISTICMANAGER_H
