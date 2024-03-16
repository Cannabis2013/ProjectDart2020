#ifndef SCORESCALCULATOR_H
#define SCORESCALCULATOR_H

#include "iscorescalculator.h"

class DartsCalculator : public IScoresCalculator {
public:
        int remaining(const QString& mod, const int& point, const int& current) override;
        Score calculate(const QString& name, const QList<Input>& inputs, const int& initial) override;
        int score(const QString& mod, const int& point) const override;

private:
        int modMultiplier(QString mod) const;
};

#endif // SCORESCALCULATOR_H
