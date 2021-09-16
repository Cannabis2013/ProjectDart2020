#ifndef DARTSCREATETERMINALTHRESHOLD_H
#define DARTSCREATETERMINALTHRESHOLD_H

#include "idartsboundaries.h"
#include <idartscreateterminalthreshold.h>
#include "idcmetainfo.h"

class DartsCreateTerminalThreshold : public IDartsCreateTerminalThreshold
{
public:
    DartsCreateTerminalThreshold(const DCBuilding::IDCMetaInfo *meta, const IDartsBoundaries *boundaries)
    {
        if(meta->terminalKeyCode() == KeyMappings::SingleModifer)
            _threshold = boundaries->singleMaxValue();
        else if(meta->terminalKeyCode() == KeyMappings::TrippleModifier)
            _threshold = boundaries->trippleMaxValue();
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
