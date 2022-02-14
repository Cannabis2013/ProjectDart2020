#ifndef DPCINPUTADDER_H
#define DPCINPUTADDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "Models/dcmeta.h"
#include "Inputs/idcinputadder.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
class DPCInputAdder : public IDCInputAdder
{
public:
    DCInput add(DCInput &input, const DCPlayer &player, const DCMeta &meta) const override;
private:
    enum PointKeyCodes{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
    int calc(DCInput &input) const;
    int createPointMultiplier(const int &code) const;
    int calculateScore(const int &point, const int &multiplier) const;
};
#endif // DARTSCONTROLLERPOINTBUILDER_H
