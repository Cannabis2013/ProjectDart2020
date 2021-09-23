#ifndef GETSCOREFROMDPCINPUT_H
#define GETSCOREFROMDPCINPUT_H

#include "DCScoresSLAs/idcgetscore.h"
#include "quuid.h"

class GetScoreFromDPCInput : public IDCGetScore
{
public:
    enum PointKeyCodes{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
    virtual int getScore(const DCContext::IDCInputModel *inputModel) const override
    {
        auto multiplier = createPointMultiplier(inputModel->modKeyCode());
        return calculateScore(inputModel->point(),multiplier);
    }
private:
    int createPointMultiplier(const int &code) const
    {
        auto pointMultiplier = code == PointKeyCodes::TrippleModifier ? 3 :
                               code == PointKeyCodes::DoubleModifier ? 2 :
                               code == PointKeyCodes::SingleModifer ? 1 : 0;
        return pointMultiplier;
    }
    int calculateScore(const int &point, const int &multiplier) const
    {
        return point*multiplier;
    }
};


#endif // POINTSCORECALCULATOR_H
