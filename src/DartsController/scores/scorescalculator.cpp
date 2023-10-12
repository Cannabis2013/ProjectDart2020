#include "scorescalculator.h"

Score ScoresCalculator::calculate(const QString& name, const QList<Input>& inputs, const int& initialScore)
{
        QList<Score> scores;
        int score = initialScore;
        for (auto& input : inputs)
                score -= inputScore(input.mod(), input.point());
        return Score(name, score);
}

Score ScoresCalculator::calculate(const Input& input, const Score& score, const QString& name)
{
        auto scoreValue = inputScore(input.mod(),input.point());
        auto newScore = score.score() - scoreValue;
        return Score(name,newScore);
}

int ScoresCalculator::inputScore(const QString& mod, const int& point) const
{
        auto multiplier = modMultiplier(mod);
        return  point*multiplier;
}

int ScoresCalculator::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}
