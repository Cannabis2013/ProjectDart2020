#include "dartscalculator.h"
#include "src/input/models/dartsinput.h"
#include "src/scores/models/Score.h"

int DartsCalculator::remaining(const DartsInput &input, const int &current)
{
    auto scoreValue = input.point() * modMultiplier(input.mod());
    return current - scoreValue;
}

Score DartsCalculator::calculate(const QString& name, const QList<DartsInput>& inputs, const int& initial)
{
    int score = initial;
    for (auto& input : inputs)
        score -= input.point() * modMultiplier(input.mod());
    if (score < 0)
        return Score(name);
    return Score(name, score);
}

int DartsCalculator::score(const DartsInput &input) const
{
    return input.point() * modMultiplier(input.mod());
}

int DartsCalculator::score(const QList<DartsInput> &inputs) const
{
    auto sum = 0;
    for (const auto &input : inputs)
        sum += score(input);
    return !inputs.isEmpty() ? sum : -1;
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
