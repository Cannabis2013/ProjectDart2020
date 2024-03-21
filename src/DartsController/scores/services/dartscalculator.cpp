#include "dartscalculator.h"
#include "src/DartsController/input/models/input.h"
#include "src/DartsController/scores/models/Score.h"

int DartsCalculator::remaining(const QString& mod, const int& point, const int& current)
{
        auto scoreValue = point * modMultiplier(mod);
        return current - scoreValue;
}

Score DartsCalculator::calculate(const QString& name, const QList<Input>& inputs, const int& initial)
{
        int score = initial;
        for (auto& input : inputs)
                score -= input.point() * modMultiplier(input.mod());
        if (score < 0)
                return Score(name);
        return Score(name, score);
}

int DartsCalculator::score(const QString& mod, const int& point) const
{
        return point * modMultiplier(mod);
}

int DartsCalculator::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}
