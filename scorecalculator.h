#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include "IPointCalculatorService.h"

class ScoreCalculator : public IPointCalculatorService
{
public:
    virtual int calculateScoreFromDartsPoint(const int &point, const int &) const override
    {
        return point;
    }
};

#endif // SCORECALCULATOR_H
