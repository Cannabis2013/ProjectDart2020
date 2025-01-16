#ifndef SCORESCALCULATOR_H
#define SCORESCALCULATOR_H

#include "iscorescalculator.h"

class DartsCalculator : public IScoresCalculator {
public:
    int remaining(const DartsInput &input, const int &current) override;
    Score calculate(const QString &name,const QList<DartsInput> &inputs,const int &initial) override;
    int score(const DartsInput &input) const override;
    int score(const QList<DartsInput> &inputs) const override;

private:
    int modMultiplier(QString mod) const;
};

#endif // SCORESCALCULATOR_H
