#ifndef POINTSCORECALCULATOR_H
#define POINTSCORECALCULATOR_H

#include "scoreCalculatorInterface.h"

class PointScoreCalculator : public ScoreCalculatorInterface
{
public:
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };

    // ScoreCalculatorInterface interface
public:
    static PointScoreCalculator* createInstance()
    {
        return new PointScoreCalculator();
    }
    virtual int calculateScore(const int &point, const int &keyCode) const override
    {
        // Initialize pointmultiplier
        auto pointMultiplier = keyCode == KeyMappings::TrippleModifier ? 3 :
                                keyCode == KeyMappings::DoubleModifier ? 2 :
                                keyCode == KeyMappings::SingleModifer ? 1 : 0;
        // Calculate point
        auto score = point*pointMultiplier;
        // Return the calculated score
        return score;
    }
};

#endif // POINTSCORECALCULATOR_H
