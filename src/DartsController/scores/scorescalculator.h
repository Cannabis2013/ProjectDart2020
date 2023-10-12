#ifndef SCORESCALCULATOR_H
#define SCORESCALCULATOR_H

#include "src/DartsController/input/Input.h"
#include "src/DartsController/scores/Score.h"

class ScoresCalculator
{
public:
        Score calculate(const QString& name, const QList<Input>& inputs, const int& initialScore);
        Score calculate(const Input& input, const Score& score, const QString& name);

private:
        int inputScore(const QString& mod, const int& point) const;
        int modMultiplier(QString mod) const;
};

#endif // SCORESCALCULATOR_H
