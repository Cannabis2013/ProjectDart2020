#ifndef DARTSCREATETERMINALTHRESHOLD_H
#define DARTSCREATETERMINALTHRESHOLD_H

#include "idartsboundaries.h"
#include <idartscreateterminalthreshold.h>
#include "idcmetainfo.h"

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
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    int _threshold;
};
#endif // DARTSGETTERMINALTHRESHOLD_H
