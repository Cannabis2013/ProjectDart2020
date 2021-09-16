#ifndef IDARTSINPUTSUGGESTIONS_H
#define IDARTSINPUTSUGGESTIONS_H

#include <qstring.h>

class IDartsInputSuggestions
{
public:
    virtual QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const = 0;
};

#endif // ILOGISTICMANAGER_H
