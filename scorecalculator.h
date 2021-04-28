#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include "scoreCalculatorInterface.h"

class ScoreCalculator : public ScoreCalculatorInterface
{
public:


    // ScoreCalculatorInterface interface
public:
    virtual int calculateScoreFromDartsPoint(const int &point, const int &) const override
    {
        return point;
    }
};

#endif // SCORECALCULATOR_H
