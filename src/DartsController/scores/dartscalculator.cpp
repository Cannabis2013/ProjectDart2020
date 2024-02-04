#include "dartscalculator.h" //
#include "src/DartsController/input/Input.h"
#include "src/DartsController/scores/Score.h"

bool DartsCalculator::isValid(const int& point, const QString& mod) const
{
        if (point > MaxPoint || point < 0)
                return false;
        return AllowedMods.contains(mod);
}

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

Score DartsCalculator::calculate(const Input& input, const Score& score, const QString& name)
{
        auto scoreValue = input.point() * modMultiplier(input.mod());
        auto newScore = score.score() - scoreValue;
        if (newScore < 0)
                return Score(name);
        return Score(name,newScore);
}

int DartsCalculator::score(const QString& mod, const int& point) const
{
        auto multiplier = modMultiplier(mod);
        return point * multiplier;
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
