#ifndef DARTSCREATETERMINALTHRESHOLD_H
#define DARTSCREATETERMINALTHRESHOLD_H

#include "DCFinishesSLAs/idartsboundaries.h"
#include "DCFinishesSLAs/idartscreateterminalthreshold.h"

class DartsCreateTerminalThreshold : public IDartsCreateTerminalThreshold
{
public:
    DartsCreateTerminalThreshold(const IDartsBoundaries *boundaries)
    {
        _threshold = boundaries->doubleMaxValue();
    }
    int threshold() const override
    {
        return _threshold;
    }
private:
    int _threshold;
};
#endif // DARTSGETTERMINALTHRESHOLD_H
